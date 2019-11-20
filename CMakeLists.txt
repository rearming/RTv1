cmake_minimum_required(VERSION 3.14)
project(RTv1 C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra)

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    add_compile_options(-Werror -O2)
endif()

include_directories(
        libft/includes
        includes)

set(sources
        sources/main.c
        sources/error.c
        sources/render/bresenham.c
        sources/hooks/hooks.c
        sources/init/init.c
        sources/render/render_utils.c)

link_directories(
        libft
        libft/ft_printf
        /usr/local/lib)

add_executable(RTv1
        ${sources}
)

target_link_libraries(RTv1
        "ft"
        "ftprintf"
        "mlx"
        "-framework OpenGL"
        "-framework AppKit"
        "-framework OpenCL")

set(test_sources
        test/test_main.c)

add_executable(test
        ${test_sources})

target_link_libraries(test
        "ft"
        "ftprintf"
        "mlx"
        "-framework OpenGL"
        "-framework AppKit"
        "-framework OpenCL")
