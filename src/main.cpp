#include <src/SDLW/window.hpp>
#include <src/SDLW/component.hpp>
#include <src/SDLW/components/elipse.hpp>
#include <src/SDLW/components/rectangle.hpp>

#include <src/boid.hpp>
#include <src/logger/logger.hpp>
static constexpr Logger logger = Logger("MAIN");

#include <thread>
#include <chrono>

const int MAX_FPS = 60;

duration time_now() {
    return std::chrono::duration_cast<duration>(std::chrono::system_clock::now().time_since_epoch());
}

int main(int argc, char* args[]) {
    auto window = SDLW::Window(1500, 800);

    // SDL_Renderer* renderer = window.get_renderer();

    SDL_GetWindowSizeInPixels(window.get_window(), &boid_sim::screen_width, &boid_sim::screen_height);

    // boid_sim::initialize(100);

    auto elipse = SDLW::Components::Elipse(400, 400, 0, 150, 100, 32, {255, 0, 255, 255});
    window.add_component(&elipse);

    auto rect = SDLW::Components::Rectangle(900, 400, 0, 200, 50, {0, 255, 255, 255});
    window.add_component(&rect);

    duration minimum_time = duration(1000000000) / MAX_FPS;
    duration previous_time = time_now();

    while(SDLW::Window::has_active_instance()) {
        window.event_update();

        duration difference = time_now() - previous_time;
        if (difference > minimum_time) {
            previous_time = time_now();

            window.graphic_update();

            elipse.rotation += 0.1;
            rect.rotation += 0.0863;

            // logger << "Frame time: " << (time_now() - previous_time).count();
            // current frame time is 500000-600000 for 100 boids
        }
    }

    return 0;
}