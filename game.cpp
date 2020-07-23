#include "game.h"
#include "logger.h"
#include "spritemanager.h"

#include <ctime>

Game* Game::m_instance = nullptr;

Game::Game()
{
}

void Game::initGame(int w, int h)
{
    instance()->init(w, h);
}

void Game::startGame()
{
    instance()->start();
}

void Game::input(SDL_Event& e)
{
    if(e.type == SDL_KEYDOWN){
        if(e.key.keysym.scancode == SDL_Scancode::SDL_SCANCODE_ESCAPE){
            m_running = false;
        }else if(m_ballOnPlate && e.key.keysym.scancode == SDL_Scancode::SDL_SCANCODE_SPACE){
            m_ballOnPlate = false;
        }else if(e.key.keysym.scancode == SDL_Scancode::SDL_SCANCODE_LEFT){
            m_platformDir = IOx;
        }else if(e.key.keysym.scancode == SDL_Scancode::SDL_SCANCODE_RIGHT){
            m_platformDir = Ox;
        }
    }else if(e.type == SDL_KEYUP){
        if(e.key.keysym.scancode == SDL_Scancode::SDL_SCANCODE_LEFT ||
                e.key.keysym.scancode == SDL_Scancode::SDL_SCANCODE_RIGHT){
            m_platformDir = None;
        }
    }
}

void Game::draw()
{
    SDL_SetRenderDrawColor(m_renderer,
                           m_windowColor.r,
                           m_windowColor.g,
                           m_windowColor.b,
                           m_windowColor.a);
    SDL_RenderClear(m_renderer);

    m_platform->draw(m_renderer);
    m_ball->draw(m_renderer);
    for(auto& i: m_blocks){
        i->draw(m_renderer);
    }

    SDL_RenderPresent(m_renderer);
}

void Game::update(float dt)
{
    SDL_Point pos = m_platform->getPos();
    SDL_Point size = {m_platform->getWidth(), m_platform->getHeight()};
    if((pos.x > 0 && m_platformDir == IOx)||
            (pos.x+size.x < m_size.x && m_platformDir == Ox)){
        m_platform->update(dt, m_platformDir);
    }
    if(!m_ballOnPlate){
        SDL_FPoint velocity = m_ball->getVelocity();
        m_ball->update(dt, Ox);
        for(auto i = m_blocks.begin(); i != m_blocks.end(); i++){
            if(getCollision(m_ball, *i)){
                velocity.x *= -1;
                delete *i;
                m_blocks.erase(i);
                break;
            }
        }
        m_ball->update(dt, Oy);
        if(getCollision(m_ball, m_platform)){
            velocity.y *= -1;
        }else
            for(auto i = m_blocks.begin(); i != m_blocks.end(); i++){
                if(getCollision(m_ball, *i)){
                    velocity.y *= -1;
                    delete *i;
                    m_blocks.erase(i);
                    break;
                }
            }
        m_ball->setVelocity(velocity);
        checkWindowCollision();
    }
}

void Game::checkWindowCollision()
{
    int width = m_ball->getWidth();
    int height = m_ball->getHeight();
    SDL_Point pos = m_ball->getPos();
    SDL_FPoint velocity = m_ball->getVelocity();

    if(pos.x <= 0 || pos.x+width >= m_size.x){
        velocity.x *= -1;
    }if(pos.y <= 0){
        velocity.y *= -1;
    }else if(pos.y+height >= m_size.y){
        m_running = false;
    }
    m_ball->setVelocity(velocity);
}

bool Game::getCollision(SpriteObject* ball, RectObject* obj)
{
    SDL_Rect ballRect = {
        ball->getPos().x,
        ball->getPos().y,
        ball->getWidth(),
        ball->getHeight()};

    SDL_Rect rect2 = {
        obj->getPos().x,
        obj->getPos().y,
        obj->getWidth(),
        obj->getHeight()};

    if (ballRect.x < rect2.x + rect2.w &&
            ballRect.x + ballRect.w > rect2.x &&
            ballRect.y < rect2.y + rect2.h &&
            ballRect.y + ballRect.h > rect2.y) {
        return true;
    }
    return false;
}

Game::~Game()
{
    delete m_platform;
    delete m_ball;
    for(auto& i: m_blocks){
        delete i;
    }
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    IMG_Quit();
}

Game *Game::instance()
{
    if(!m_instance)
        m_instance = new Game();
    return m_instance;
}

void Game::drawIntro(){
    SDL_Texture* texture = SpriteManager::instance()->getSprite("intro");
    SDL_Point textureSize;
    SDL_QueryTexture(texture, NULL, NULL, &textureSize.x, &textureSize.y);
    SDL_Rect dest = {(m_size.x-textureSize.x)/2,
                    (m_size.y-textureSize.y)/2,
                    textureSize.x,
                    textureSize.y};
    SDL_RenderCopy(m_renderer, texture, nullptr, &dest);
    SDL_RenderPresent(m_renderer);
    SDL_Event e;
    bool quit = false;
    while(!quit){
        while(SDL_PollEvent(&e))
            if(e.type == SDL_KEYDOWN)
                quit = true;
    }
}

void Game::start()
{
    setupObjects(m_size.x, m_size.y);
    m_running = true;
    float frameDelay = 1000.f/m_fps;
    float frameStart;
    float ticks;
    if(!m_window){
        Logger::error("No window created");
        return;
    }
    if(!m_renderer){
        Logger::error("No renderer created");
        return;
    }
    SDL_Event e;
    drawIntro();
    while(m_running){
        frameStart = SDL_GetTicks();
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                m_running = false;
                break;
            }else{
                input(e);
            }
        }
        update(frameDelay);
        draw();
        ticks = SDL_GetTicks() - frameStart;
        if(frameDelay > ticks){
            SDL_Delay(frameDelay-ticks);
        }
        if(checkWin()){
            m_running = false;
        }
    }
    if(checkWin())
        drawEnd(SpriteManager::instance()->getSprite("win"));
}

bool Game::checkWin(){
    return m_blocks.size() == 0;
}

void Game::drawEnd(SDL_Texture* texture){
    SDL_Point textureSize;
    SDL_QueryTexture(texture, NULL, NULL, &textureSize.x, &textureSize.y);
    SDL_Rect dest = {(m_size.x-textureSize.x)/2,
                    (m_size.y-textureSize.y)/2,
                    textureSize.x,
                    textureSize.y};
    SDL_RenderCopy(m_renderer, texture, nullptr, &dest);
    SDL_RenderPresent(m_renderer);
    SDL_Event e;
    bool quit = false;
    while(!quit){
        while(SDL_PollEvent(&e))
            if(e.type == SDL_KEYDOWN &&
                    e.key.keysym.scancode == SDL_Scancode::SDL_SCANCODE_ESCAPE)
                quit = true;
            else if(e.type == SDL_KEYDOWN &&
                    e.key.keysym.scancode == SDL_Scancode::SDL_SCANCODE_SPACE)
                start();
    }
}

void Game::setupObjects(int w, int h){
    int platform_width = 0.2*w;
    int platform_height = 0.03*w;
    int platform_x = (w-platform_width)/2;
    int platform_y = h-platform_height;

    int ball_size = 0.03*w;
    float ball_x_velocity = (10+rand()%30)/100.f;
    float ball_y_velocity = (10+rand()%30)/-100.f;
    Logger::log(ball_x_velocity);
    Logger::log(ball_y_velocity);
    if(m_platform == nullptr){
        m_platform = new RectObject({platform_x, platform_y},
                                platform_width,
                                platform_height);
        m_platform->setBorder(2);
        m_platform->setBaseColor({106, 4, 15, 255});
        m_platform->setBorderColor({55, 6, 23, 255});
        m_platform->setVelocity({0.5f, 0.5f});
    }else{
        m_platform->setPos({platform_x, platform_y});
    }
    if(m_ball == nullptr){
        m_ball = new SpriteObject({platform_x+(platform_width-ball_size)/2,
                                   platform_y-platform_height},
                                  ball_size,
                                  ball_size);
        m_ball->setSprite(SpriteManager::instance()->getSprite("ball"));
    }else{
        m_ball->setPos({platform_x+(platform_width-ball_size)/2,
                            platform_y-platform_height});
    }
    m_ball->setVelocity({ball_x_velocity, ball_y_velocity});

    const int lines = 4;
    string config[lines] = {
        "1111111111",
        "0011111100",
        "0001111000",
        "0000110000"
    };
    RectObject* obj;
    int blocks_start_x = 0;
    int blocks_start_y = 40;
    int blocks_width = w;
    int blocks_height = 200;

    int one_block_width = (blocks_start_x+blocks_width)/config->size();
    int one_block_height = (blocks_start_y+blocks_height)/lines;
    int y = blocks_start_y;
    for(int i = 0; i < lines; i++){
        int x = blocks_start_x;
        for(size_t j = 0; j < config->size(); j++){
            if(config[i][j] != '0'){
                obj = new RectObject({x, y}, one_block_width, one_block_height);
                obj->setBaseColor({214, 40, 40, 255});
                obj->setBorderColor({0, 0, 0, 0});
                obj->setBorder(2);
                m_blocks.push_back(obj);
            }
            x += one_block_width;
        }
        y += one_block_height;
    }

    Logger::log("Objects created");
}

void Game::init(int w, int h)
{
    m_size = {w, h};
    srand(time(0));
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        Logger::error(SDL_GetError());
        return;
    }
    Logger::log("SDL initialized");

    int image_flags = IMG_INIT_PNG;
    if(!(IMG_Init(image_flags)&image_flags)){
        Logger::error(IMG_GetError());
    }
    Logger::log("IMG initialized");

    m_window = SDL_CreateWindow("Arcanoid", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
    if(!m_window){
        Logger::error(SDL_GetError());
        return;
    }
    Logger::log("Window created");

    m_renderer = SDL_CreateRenderer(m_window, -1,
                                    SDL_RENDERER_ACCELERATED|SDL_RENDERER_TARGETTEXTURE);
    if(!m_renderer){
        Logger::error(SDL_GetError());
        return;
    }
    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
    Logger::log("Renderer created");

    SpriteManager::instance()->addSprite(m_renderer, "ball" ,"./ballSprite.png");
    SpriteManager::instance()->addSprite(m_renderer, "intro", "../intro.png");
    SpriteManager::instance()->addSprite(m_renderer, "win", "../win.png");
    Logger::log("Sprite manager initialized");
}
