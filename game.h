#ifndef GAME_H
#define GAME_H

#include "rectobject.h"
#include "spriteobject.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

using namespace std;
class Game
{
    enum CollisionSide{
        None, Top, Bottom, Left, Right
    };
public:
    ~Game();
    static Game* instance();
    static void initGame(int w, int h);
    static void startGame();
    void input(SDL_Event& e);
    void update(float dt);
    void draw();
    void checkWindowCollect();
    void collisionDetect();
    CollisionSide getCollision(SpriteObject* ball, RectObject* obj);

private:
    static Game* m_instance;
    Game();
    void init(int w, int h);
    void start();

    SDL_Renderer* m_renderer = nullptr;
    SDL_Window* m_window = nullptr;
    SDL_Point m_size;
    bool m_running = true;
    Color m_windowColor{3, 7, 30, 255};
    int m_fps = 60;
    bool m_ballOnPlate = true;

    vector<RectObject*> m_blocks;
    RectObject* m_platform = nullptr;
    SpriteObject* m_ball = nullptr;
};

#endif // GAME_H
