#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <map>
#include <string>
#include <fstream>
using namespace std;

class Game;

class SpriteManager
{
public:
    static SpriteManager* instance();
    ~SpriteManager();
    void addSprite(SDL_Renderer* render, string tag, const string& path);
    SDL_Texture* getSprite(string tag);

private:
    SpriteManager();
    static SpriteManager* m_instance;
    map<string, SDL_Texture*> m_sprites;
};

#endif // TEXTUREMANAGER_H
