#pragma once

#include <stdexcept>
#include <forward_list>

#include <SDL2/SDL.h>

#include <src/SDLW/component.hpp>

#include <src/logger/logger.hpp>

namespace SDLW {
class Window {

private:
    static constexpr Logger logger = Logger("SDLW Window");

    static uint8_t count; // number of windows, set to 0 at bottom of file

    bool alive = true;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    
    std::forward_list<SDLW::Component *> components;

public:
    Window(int width = 640, int height = 480) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            logger.log(Logger::CRITICAL) << "SDL could not initialize! SDL_Error: %s\n" << SDL_GetError();
            throw std::runtime_error("SDL failed to initialize");
        } 
        window = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            logger.log(Logger::CRITICAL) << "Window could not be created! SDL_Error: %s\n" << SDL_GetError();
            throw std::runtime_error("Window failed to initialize");
        } 
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == NULL) {
            logger.log(Logger::CRITICAL) << SDL_GetError();
            throw std::runtime_error("Renderer component failed to initialize");
        }
        count++;   
        logger << "Window " << get_id() << " successfully created!";        
    }

    void event_update() {
        SDL_Event e; 
        bool quit = false; 
        while (SDL_PollEvent(&e)) { 
            if( e.type == SDL_QUIT ) quit = true;
        }
        if (quit) {
            int id = get_id();
            SDL_DestroyWindow(window);
            alive = false;
            count--;
            logger << "Window " << id << " closed by user";
            check_sdl_quit();
        }
    }

    void graphic_update() {
        for(Component * component : components){
            component->update(renderer);
        }   

        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);
        SDL_RenderClear(renderer);
    }

    template<typename T>
    void add_component(T * component) {
        components.push_front(component);
    }

    SDL_Renderer * get_renderer() {
        return renderer;
    }
    SDL_Window * get_window() {
        return window;
    }

    int get_id() {
        return SDL_GetWindowID(window);
    }
    bool is_alive() {
        return alive;
    }

    ~Window() {
        if (alive) {
            int id = get_id();
            SDL_DestroyWindow(window);
            count--;
            logger << "Window " << id << " closed automatically, window instance was destroyed";
            check_sdl_quit();
        }
    }

    static bool has_active_instance() {
        return count;
    }
    static int get_active_instances() {
        return count;
    }

private:
    void check_sdl_quit() {
        if (count == 0) {
            SDL_Quit();
            logger << "All windows closed, SDL quit";
        }
    }
};

}

uint8_t SDLW::Window::count = 0;