cmake_minimum_required(VERSION 3.14)
project(RTv1 C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra)

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    add_compile_options(-O2)
endif()

# <----RTv1 compile---->

set(sources
        sources/main.c
        sources/error.c
        sources/init/init.c
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
        sources/render/render.c
        sources/parsing/scene_config_parser.c
        sources/parsing/object_getter.c
        sources/parsing/object_parsing_utils.c
        sources/parsing/scene_parsing.h
        sources/parsing/light_getter.c
        sources/parsing/parsing_loops.c
        sources/parsing/camera_getter.c
        sources/debug/debug_utils.c
        sources/debug/debug_print_objects.c)

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    INCLUDE(FindPkgConfig)
    PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
    PKG_SEARCH_MODULE(OPENCL REQUIRED OpenCL)

    set(graphic_libs_include_dirs
            ${SDL2_INCLUDE_DIRS})
    set(graphic_libs_dirs
            ${SDL2_LIBRARY_DIRS})
    set(graphic_libs_link_names
            ${SDL2_LIBRARIES}
            ${OPENCL_LIBRARIES})
else()
    set(graphic_libs_include_dirs
            SDL2_libs/SDL2.framework/Headers)
    set(graphic_libs_dirs
            SDL2_libs/)
    set(graphic_libs_link_names
            "-F ${PROJECT_SOURCE_DIR}/SDL2_libs -framework SDL2"
            "-framework OpenCL")
endif()

message("graphic_libs_include_dirs: " ${graphic_libs_include_dirs})
message("graphic_libs_dirs: " ${graphic_libs_dirs})
message("graphic_libs_link_names: " ${graphic_libs_link_names})

include_directories(
        libft/includes
        includes
        ${graphic_libs_include_dirs}
        )

link_directories(
        libft
        libft/ft_printf
        ${graphic_libs_dirs}
)

add_executable(RTv1
        ${sources}
)

target_link_libraries(RTv1
        "ftprintf"
        "ft"
        ${graphic_libs_link_names}
        "m"
        )

# <----TESTING----> #

set(test_sources
        test/test_main.c)

add_executable(test
        ${test_sources})

target_link_libraries(test
        "ftprintf"
        "ft")
