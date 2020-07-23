#include "object.h"

Object::Object(SDL_Point pos):
    m_pos(pos)
{

}

void Object::update(float dt, Axis axis)
{
}

void Object::move(int dx, int dy)
{
    m_pos.x += dx;
    m_pos.y += dy;
}

SDL_Point Object::getPos()
{
    return m_pos;
}

void Object::setPos(SDL_Point pos)
{
    m_pos = pos;
}
