#pragma once

#include <SDL2/SDL.h>

#include <src/logger/logger.hpp>
#include <vector>
#include <chrono>

using duration = std::chrono::nanoseconds;

namespace boid_sim {
    static constexpr Logger logger = Logger("BOIDSIM");

    int screen_width = 1500;
    int screen_height = 800;

    float protected_range = 40; // px
    float visual_range = 150; // px
    float screen_margin = 150;
    float turn_factor = 1000;
    float centering_factor = 0.4;
    float avoid_factor = 12;
    float matching_factor = 2;
    float max_speed = 550;
    float min_speed = 300;

    float max_bias = 0.01;
    float bias_increment = 0.00004;

    const float BOID_SIZE = 10; // px radius
    const SDL_Color BOID_COLOR = {255, 5, 5, 255};

    const float back_angle_1 = M_PI*3/4;
    const float back_angle_2 = M_PI*5/4;

    struct boid {
        float x, y;
        float vx, vy;
        bool g;
        float b = 0.001;
        boid(bool _group = false): 
        g(_group) {}
        boid(float _x, float _y, bool _group = false):
        x(_x), y(_y), vx(0), vy(0), g(_group) {}
        boid(float _x, float _y, float _vx, float _vy, bool _group = false):
        x(_x), y(_y), vx(_vx), vy(_vy), g(_group) {}
    };

    std::vector<boid> boid_list;

    void initialize(const int boid_count, const float group_distribution = 0.5) {
        boid_list.resize(boid_count);
        for (int i = 0; i < boid_count; i++) {
            boid_list[i] = boid(rand()%screen_width, rand()%screen_height, rand()%600-300, rand()%600-300, (i/(boid_count-1.0) > group_distribution));
        } 
    }
    void update(duration delta) {
        float ds = delta.count() / 1000000000.0;
        for (u_int i = 0; i < boid_list.size(); i++) { // for each boid
            boid & b = boid_list[i];

            float dx_close=0, dy_close=0;
            float vx_avg=0, vy_avg=0, visible_count=0;
            float x_avg=0, y_avg=0;

            for (u_int j = 0; j < boid_list.size(); j++) if (j != i) { // for each other boid
                boid & o = boid_list[j];
                float dist = std::sqrt(std::pow(b.x-o.x, 2) + std::pow(b.y-o.y, 2));

                if (dist < visual_range) {
                    if (dist < protected_range) {
                        // separation
                        dx_close += b.x-o.x;
                        dy_close += b.y-o.y;
                    } else {
                        // alignment
                        vx_avg += o.vx;
                        vy_avg += o.vy;
                        // cohesion
                        x_avg += o.x;
                        y_avg += o.y;
                        // count
                        visible_count++;
                    }
                }
            }

            // separation
            b.vx += dx_close*avoid_factor*ds;
            b.vy += dy_close*avoid_factor*ds;

            if (visible_count > 0) {
                // alignment and bohesion
                vx_avg /= visible_count;
                vy_avg /= visible_count;
                x_avg /= visible_count;
                y_avg /= visible_count;
                b.vx += (vx_avg - b.vx)*matching_factor*ds + (x_avg - b.x)*centering_factor*ds;
                b.vy += (vy_avg - b.vy)*matching_factor*ds + (y_avg - b.y)*centering_factor*ds;
            }

            // screen edges
            if (b.x < screen_margin) {
                b.vx += turn_factor*ds;
            }                 
            else if (b.x > screen_width  - screen_margin) {
                b.vx -= turn_factor*ds;
            } 
            else if (b.y < screen_margin) {
                b.vy += turn_factor*ds;
            }                
            else if (b.y > screen_height - screen_margin) {
                b.vy -= turn_factor*ds;
            }

            // bias update
            if ((b.vx < 0) ^ b.g) b.b = std::min(max_bias, b.b + bias_increment*ds);
            else                  b.b = std::max(bias_increment, b.b - bias_increment*ds);

            // bias
            b.vx = (1-b.b)*b.vx + b.b*(b.g?1:-1);


            // speed limiters
            float speed = std::sqrt(b.vx*b.vx + b.vy*b.vy);
            if (speed < min_speed) {
                b.vx = (b.vx/speed)*min_speed;
                b.vy = (b.vy/speed)*min_speed;
            }
            else if (speed > max_speed) {
                b.vx = (b.vx/speed)*max_speed;
                b.vy = (b.vy/speed)*max_speed;
            }

            // update
            b.x += b.vx * ds;
            b.y += b.vy * ds;
        }
    }
    void draw_to(SDL_Renderer* renderer) {
        for (u_int i = 0; i < boid_list.size(); i++) {
            boid & b = boid_list[i];
            float a = std::atan2(b.vy, b.vx);

            SDL_Vertex verticies[3];
            verticies[0] = {
                {std::cos(a)*BOID_SIZE + b.x, std::sin(a)*BOID_SIZE + b.y},
                BOID_COLOR
            };
            verticies[1] = {
                {std::cos(a + back_angle_1)*BOID_SIZE + b.x, std::sin(a + back_angle_1)*BOID_SIZE + b.y},
                BOID_COLOR
            };
            verticies[2] = {
                {std::cos(a + back_angle_2)*BOID_SIZE + b.x, std::sin(a + back_angle_2)*BOID_SIZE + b.y},
                BOID_COLOR
            };
            SDL_RenderGeometry(renderer, NULL, verticies, 3, NULL, 3);
        }
    }
}