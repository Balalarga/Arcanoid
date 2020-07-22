#include "spritemanager.h"
#include "logger.h"

SpriteManager* SpriteManager::m_instance = nullptr;

SpriteManager *SpriteManager::instance()
{
    if(!m_instance)
        m_instance = new SpriteManager();
    return m_instance;
}

SpriteManager::SpriteManager()
{
}


SpriteManager::~SpriteManager(){
    for(auto& i: m_sprites){
        SDL_DestroyTexture(i.second);
    }
}

void SpriteManager::addSprite(SDL_Renderer* render, string tag, const string &path)
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if(!loadedSurface){
        Logger::error("Unable to load image "+path);
        Logger::error(IMG_GetError());
    }else{
        newTexture = SDL_CreateTextureFromSurface(render, loadedSurface);
        if(!newTexture){
            Logger::error("Unable to create texture from "+path);
            Logger::error(IMG_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }
    m_sprites[tag] = newTexture;
}

SDL_Texture* SpriteManager::getSprite(string tag)
{
    if(m_sprites.find(tag) == m_sprites.end()){
        Logger::error("Texture "+tag+" doesn't exists");
        return nullptr;
    }
    return m_sprites[tag];
}
