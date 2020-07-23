#ifndef OBJECT_H
#define OBJECT_H

#include <SDL2/SDL.h>

struct Color{
    Uint8 r, g, b, a;
};

enum Axis{
    None, All, IAll, Ox, Oy, IOx, IOy
};

class Object
{
public:
    Object(SDL_Point pos);
    virtual ~Object(){}
    virtual void draw(SDL_Renderer* render) = 0;
    virtual void update(float dt, Axis axis = All);
    virtual void move(int dx, int dy);
    SDL_Point getPos();
    void setPos(SDL_Point pos);

protected:
    SDL_Point m_pos;
};

#endif // OBJECT_H
