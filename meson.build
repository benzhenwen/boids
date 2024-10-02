project('boids', 'cpp',
        default_options: 'default_library=static')

sdl2_dep = dependency('sdl2')

executable('boids', 'src/main.cpp',
           win_subsystem: 'windows',
           dependencies: sdl2_dep)