cmake_minimum_required(VERSION 3.14)
project(RTv1 C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra -O2)

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    add_compile_options( -Werror)
endif()

# <----RTv1 compile---->

include_directories(
        libft/includes
        includes
        SDL2_libs/SDL2.framework/Headers)

set(sources
        sources/main.c
        sources/error.c
        sources/init/init.c
        sources/init/primitives.c
        sources/init/init_scene.c
        sources/hooks/moves.c
        sources/hooks/event_processing.c
        sources/SDL_utils/sdl_loop.c
        sources/exit_clean.c
        sources/math_utils/vector_math.c
        sources/math_utils/math_utils.c
        sources/math_utils/rotation.c
        sources/math_utils/vector_math2.c
        sources/open_cl/cl_init.c
        sources/open_cl/cl_files_parser.c
        sources/open_cl/cl_render.c
        sources/open_cl/cl_memory_management.c
        sources/open_cl/cl_debug_info.c
        sources/render/render.c
        sources/parsing/scene_config_parser.c
        )

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
