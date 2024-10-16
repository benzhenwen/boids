#pragma once

#include <vector>

#include <SDL2/SDL.h>

#include <src/SDLW/component.hpp>

#include <iostream>

namespace SDLW::Components {
class Elipse: 
public Component, 
public Component::Rotated, 
public Component::Colored {

protected:
    std::vector<SDL_Vertex> verticies;
    std::vector<int> indicies;

    void create_verticies() {
        for (uint i = 0; i < verticies.size(); i++) {
            float a = ((float) i) / verticies.size() * M_PI * 2;
            float temp_x = std::cos(a) * w;
            float temp_y = std::sin(a) * h;
            verticies[i] = {
                {x + temp_x*std::cos(rotation) - temp_y*std::sin(rotation), y + temp_x*std::sin(rotation) + temp_y*std::cos(rotation)},
                color
            };
        }

        if (indicies.size() != (verticies.size()-2)*3) {
            indicies.resize(   (verticies.size()-2)*3);
            int j = 1;
            for (uint i = 0; i < indicies.size(); i += 3) {
                indicies[i] = 0;
                indicies[i+1] = j;
                indicies[i+2] = ++j;
            }
        }
    }

    inline void push_stage() override {
        create_verticies();
    }

    inline void render_to(SDL_Renderer * renderer) override {
        SDL_RenderGeometry(renderer, NULL, verticies.data(), verticies.size(), indicies.data(), indicies.size()); 
    }

public:
    Stagable<float> w, h;
    
    Elipse(float _x, float _y, float _rotation, float _w, float _h, int _verticies, Color _color): 
    Component(_x, _y),
    Component::Rotated(_rotation, *this),
    Component::Colored(_color, *this),
    w(_w, *this),
    h(_h, *this),
    verticies(_verticies) {
        create_verticies();
    }
};
}