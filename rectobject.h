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
    void setBaseColor(Color c);
    void setBorderColor(Color c);
    void setBorder(int border);

    int getWidth();
    int getHeight();
protected:
    int m_width;
    int m_height;
    int m_border;

    Color m_baseColor;
    Color m_borderColor;
};

#endif // RECTOBJECT_H
