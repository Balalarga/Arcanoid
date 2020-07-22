#ifndef OBJECT_H
#define OBJECT_H

#include <SDL2/SDL.h>

struct Color{
    Uint8 r, g, b, a;
};

class Object
{
public:
    Object(SDL_Point pos);
    virtual ~Object(){}
    virtual void draw(SDL_Renderer* render) = 0;
    virtual void update(float dt);
    virtual void move(int dx, int dy);
    SDL_Point getPos();

protected:
    SDL_Point m_pos;
};

#endif // OBJECT_H
