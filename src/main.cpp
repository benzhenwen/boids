#include <SDL2/SDL.h>

#include <src/logger/logger.hpp>

constexpr Logger logger = Logger("MAIN");

int main(int argv, char** args) {
    logger << 69 << " haha funny";

    // //The window we'll be rendering to
    // SDL_Window* window = NULL;
    
    // //The surface contained by the window
    // SDL_Surface* screenSurface = NULL;

    // //Initialize SDL
    // if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    // {
    //     printf( "SDL could not initialize! SDL_Error: %s\n", "shit" );
    // }

    return 0;
}