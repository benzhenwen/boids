#pragma once

#include <SDL2/SDL.h>

#include <src/SDLW/component.hpp>

namespace SDLW::Components {
class Rectangle: public Component {
protected:
    

public:
    float w, h;
    Color color;

    Rectangle(float _x, float _y, float _rotation, float _w, float _h, int _vertex_count, Color _color): 
    Component(_x, _y, _rotation),
    w(_w),
    h(_h),
    color(_color) {};
};
}