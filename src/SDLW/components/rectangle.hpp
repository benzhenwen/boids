#pragma once

#include <vector>

#include <SDL2/SDL.h>

#include <src/SDLW/component.hpp>

namespace SDLW::Components {
class Rectangle: 
public Component,
public Component::Rotated,
public Component::Colored {

protected:
    SDL_Vertex verticies[4];
    static constexpr int indicies[6] = {0, 1, 2, 0, 2, 3};

    void create_verticies() {
        verticies[0] = {
            {x, y},
            color
        };
        verticies[1] = {
            {x + w*std::cos(rotation), y + w*std::sin(rotation)},
            color
        };
        verticies[2] = {
            {x + w*std::cos(rotation) - h*std::sin(rotation), y + w*std::sin(rotation) + h*std::cos(rotation)},
            color
        };
        verticies[3] = {
            {x - h*std::sin(rotation), y + h*std::cos(rotation)},
            color
        };
    }
    inline void push_stage() override {
        create_verticies();
    }
    inline void render_to(SDL_Renderer * renderer) override {
        SDL_RenderGeometry(renderer, NULL, verticies, 4, indicies, 6);
    }

public:
    Stagable<float> w, h;

    Rectangle(float _x, float _y, float _rotation, float _w, float _h, Color _color): 
    Component(_x, _y),
    Component::Rotated(_rotation, *this),
    Component::Colored(_color, *this),
    w(_w, *this),
    h(_h, *this) {
        create_verticies();
    };
};
}