#include "spriteobject.h"

SpriteObject::SpriteObject(SDL_Point pos, int w, int h):
    Object(pos),
    m_width(w),
    m_height(h)
{
}

void SpriteObject::draw(SDL_Renderer *render)
{
    if(!m_sprite)
        return;
    SDL_Rect dest{m_pos.x, m_pos.y, m_width, m_height};
    SDL_RenderCopy(render, m_sprite, nullptr, &dest);
}

void SpriteObject::scale(float sx, float sy)
{
    int new_width = m_width*sx;
    int new_height = m_height*sy;
    int d_width = m_width-new_width;
    int d_height = m_height-new_height;
    m_pos.x += d_width>>1;
    m_pos.y += d_height>>1;
    m_width = new_width;
    m_height = new_height;
}

void SpriteObject::setSprite(SDL_Texture *sprite)
{
    m_sprite = sprite;
}

void SpriteObject::update(float dt)
{
    m_pos.x += dt*m_velocity.x;
    m_pos.y += dt*m_velocity.y;
}

void SpriteObject::setVelocity(SDL_FPoint v)
{
    m_velocity.x = v.x;
    m_velocity.y = v.y;
}

int SpriteObject::getWidth()
{
    return m_width;
}

int SpriteObject::getHeight()
{
    return m_height;
}

SDL_FPoint SpriteObject::getVelocity()
{
    return m_velocity;
}
