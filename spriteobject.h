#ifndef SPRITEOBJECT_H
#define SPRITEOBJECT_H

#include "object.h"
#include <SDL2/SDL_image.h>

class SpriteObject: public Object
{
public:
    SpriteObject(SDL_Point pos, int w, int h);
    void draw(SDL_Renderer *render) override;
    void scale(float sx, float sy);
    void setSprite(SDL_Texture* sprite);
    void update(float dt) override;
    void setVelocity(SDL_FPoint v);
    int getWidth();
    int getHeight();
    SDL_FPoint getVelocity();

private:
    SDL_Texture* m_sprite = nullptr;
    int m_width, m_height;
    SDL_FPoint  m_velocity;
};

#endif // SPRITEOBJECT_H
