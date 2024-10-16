#pragma once

#include <vector>

#include <SDL2/SDL.h>

#include <src/SDLW/component.hpp>

#include <iostream>

namespace SDLW::Components {
class Circle: 
public Component, 
public Component::Colored {

protected:
    std::vector<SDL_Vertex> verticies;
    std::vector<int> indicies;

    void create_verticies() {
        for (uint i = 0; i < verticies.size(); i++) {
            float a = ((float) i) / verticies.size() * M_PI * 2;
            verticies[i] = {
                {x + std::cos(a) * radius , y + std::sin(a) * radius},
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
    Stagable<float> radius;
    
    Circle(float _x, float _y, float _radius, int _verticies, Color _color): 
    Component(_x, _y),
    Component::Colored(_color, *this),
    radius(_radius, *this),
    verticies(_verticies) {
        create_verticies();
    }
};
}