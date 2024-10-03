#include <SDL2/SDL.h>

#include <src/boid.hpp>
#include <src/logger/logger.hpp>
static constexpr Logger logger = Logger("MAIN");

#include <thread>
#include <chrono>

const int SCREEN_WIDTH = 1500;
const int SCREEN_HEIGHT = 800;
const int MAX_FPS = 60;

duration time_now() {
    return std::chrono::duration_cast<duration>(std::chrono::system_clock::now().time_since_epoch());
}

int main(int argc, char* args[]) {

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    } else {
        window = SDL_CreateWindow( "Boids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL ) {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        } else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

            if (renderer == NULL) {
                logger.log(Logger::CRITICAL) << SDL_GetError();
                return 1;
            }

            SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);

            boid_sim::initialize(40);
            SDL_RenderClear(renderer);
            boid_sim::draw_to(renderer);
            SDL_RenderPresent(renderer);

            duration minimum_time = duration(1000000000) / MAX_FPS;
            duration previous_time = time_now();

            SDL_Event e; 
            bool quit = false; 
            while(quit == false) { 
                while(SDL_PollEvent(&e)){ 
                    if( e.type == SDL_QUIT ) quit = true; 
                }

                duration difference = time_now() - previous_time;
                if (difference > minimum_time) {
                    previous_time = time_now();

                    boid_sim::update(difference);
                    SDL_RenderClear(renderer);
                    boid_sim::draw_to(renderer);
                    SDL_RenderPresent(renderer);
                }
            }
        }
    }

    //Destroy window
    SDL_DestroyWindow( window );

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}