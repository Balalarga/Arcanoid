#include "rectobject.h"

RectObject::RectObject(SDL_Point pos, int w, int h):
    Object(pos),
    m_width(w),
    m_height(h),
    m_baseColor{0, 0, 0, 0},
    m_borderColor{0, 0, 0, 0}
{
}

RectObject::~RectObject()
{
}

void RectObject::draw(SDL_Renderer* render)
{
    SDL_Rect border{m_pos.x, m_pos.y, m_width, m_height};
    SDL_Rect rect{border.x + m_border,
                    border.y + m_border,
                    border.w - (m_border<<1),
                    border.h - (m_border<<1)};

    Color defColor;
    SDL_GetRenderDrawColor(render,
                           &defColor.r,
                           &defColor.g,
                           &defColor.b,
                           &defColor.a);


    SDL_SetRenderDrawColor(render,
                           m_borderColor.r,
                           m_borderColor.g,
                           m_borderColor.b,
                           m_borderColor.a);
    SDL_RenderFillRect(render, &border);

    SDL_SetRenderDrawColor(render,
                           m_baseColor.r,
                           m_baseColor.g,
                           m_baseColor.b,
                           m_baseColor.a);
    SDL_RenderFillRect(render, &rect);


    SDL_SetRenderDrawColor(render,
                           defColor.r,
                           defColor.g,
                           defColor.b,
                           defColor.a);
}

void RectObject::update(float dt, Axis axis)
{
    if(axis == None)
        return;
    if(axis == All || axis == Ox)
        m_pos.x += dt*m_velocity.x;
    if(axis == All || axis == Oy)
        m_pos.y += dt*m_velocity.y;
    if(axis == IAll || axis == IOx)
        m_pos.x -= dt*m_velocity.x;
    if(axis == IAll || axis == IOy)
        m_pos.y -= dt*m_velocity.y;
}

int RectObject::getWidth()
{
    return m_width;
}

int RectObject::getHeight()
{
    return m_height;
}

SDL_FPoint RectObject::getVelocity()
{
    return m_velocity;
}

void RectObject::setVelocity(SDL_FPoint v)
{
    m_velocity.x = v.x;
    m_velocity.y = v.y;
}
void RectObject::setBaseColor(Color c)
{
    m_baseColor = c;
}

void RectObject::setBorderColor(Color c)
{
    m_borderColor = c;
}

void RectObject::setBorder(int border)
{
    m_border = border;
}
