#pragma once

#include <vector>

#include <SDL2/SDL.h>

#include <src/SDLW/component.hpp>

#include <iostream>

namespace SDLW::Components {
class Elipse: public Component {
protected:
    float w, h;
    Color color;
public:
    float stage_w = w;
    float stage_h = h;
    Color stage_color = color;

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

        indicies.resize((verticies.size()-2)*3);
        int j = 1;
        for (uint i = 0; i < indicies.size(); i += 3) {
            indicies[i] = 0;
            indicies[i+1] = j;
            indicies[i+2] = ++j;
        }
    }
    void offset_verticies(float x, float y) {
        for (uint i = 0; i < verticies.size(); i++) {
            verticies[i].position.x += x;
            verticies[i].position.y += y;
        }
    }

    void push_stage() override {
        bool just_move = (rotation == stage_rotation && w == stage_w && h == stage_h && color == stage_color);
        if (just_move) offset_verticies(stage_x - x, stage_y - y);

        x = stage_x;
        y = stage_y;
        rotation = stage_rotation;
        w = stage_w;
        h = stage_h;
        color = stage_color;

        if (!just_move) create_verticies();
    }

    inline void render_to(SDL_Renderer * renderer) override {
        SDL_RenderGeometry(renderer, NULL, verticies.data(), verticies.size(), indicies.data(), indicies.size()); 
    }

public:
    Elipse(float _x, float _y, float _rotation, float _horizontal_magnitude, float _vertical_magnitude, int _vertex_count, Color _color): 
    Component(_x, _y, _rotation),
    w(_horizontal_magnitude),
    h(_vertical_magnitude),
    color(_color),
    verticies(_vertex_count) {
        create_verticies();
    }
};
}