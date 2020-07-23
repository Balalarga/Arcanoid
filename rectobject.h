#ifndef RECTOBJECT_H
#define RECTOBJECT_H

#include <SDL2/SDL.h>
#include "object.h"

class RectObject: public Object
{
public:
    RectObject(SDL_Point pos, int w, int h);
    virtual ~RectObject();

    virtual void draw(SDL_Renderer* render) override;
    void update(float dt, Axis axis = All) override;
    void setBaseColor(Color c);
    void setBorderColor(Color c);
    void setBorder(int border);
    int getWidth();
    int getHeight();

    SDL_FPoint getVelocity();
    void setVelocity(SDL_FPoint v);
protected:
    int m_width;
    int m_height;
    int m_border;

    Color m_baseColor;
    Color m_borderColor;

    SDL_FPoint  m_velocity;
};

#endif // RECTOBJECT_H
