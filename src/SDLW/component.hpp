#pragma once

#include <SDL2/SDL.h>

namespace SDLW {
class Component {
friend class Window;

public:
struct Color: public SDL_Color {
    bool operator==(Color other) {
        return
            r == other.r &&
            g == other.g &&
            b == other.b &&
            a == other.a;
    }
};

protected:
    float x, y;
    float rotation;
public:
    float stage_x = x;
    float stage_y = y;
    float stage_rotation = rotation;

    float get_x() { return x; }
    float get_y() { return y; }
    float get_rotation() { return rotation; }

protected:
    Component(float _x, float _y, float _rotation):
    x(_x), y(_y), rotation(_rotation) {};

    virtual void push_stage() = 0;
    virtual void render_to(SDL_Renderer * renderer) = 0;
    inline void update(SDL_Renderer * renderer) {
        push_stage();
        render_to(renderer);
    }
};
}