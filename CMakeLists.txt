cmake_minimum_required(VERSION 3.14)
project(RTv1 C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra)

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    add_compile_options(-Werror -O2)
endif()

# <----RTv1 compile---->

include_directories(
        libft/includes
        includes
        SDL2_libs/SDL2.framework/Headers)

set(sources
        sources/main.c
        sources/error.c
        sources/render/bresenham.c
        sources/hooks/hooks.c
        sources/init/init.c
        sources/render/render_utils.c
        sources/SDL_utils/sdl_clean.c
        sources/SDL_utils/sdl_loop.c
        sources/SDL_utils/sdl_exit.c
        sources/render/ray_sphere_intersect.c
        sources/math_utils/vector_math.c
        sources/math_utils/math_utils.c
        sources/render/render.c
        sources/open_cl/cl_gnl.c
        sources/open_cl/cl_init.c)

link_directories(
        libft
        libft/ft_printf
        SDL2_libs/
)

add_executable(RTv1
        ${sources}
)

target_link_libraries(RTv1
        "ft"
        "ftprintf"
        "-F ${PROJECT_SOURCE_DIR}/SDL2_libs -framework SDL2"
        "-framework OpenCL")

# <----TESTING----> #

set(test_sources
        test/test_main.c)

add_executable(test
        ${test_sources})

target_link_libraries(test
        "ft"
        "ftprintf")
