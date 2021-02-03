cmake_minimum_required(VERSION 3.17)
project(miniRT C)

set(CMAKE_C_STANDARD 99)

add_executable(miniRT
        convertors.c
        ft_printf.h
        ft_ssplit.c
        get_next_line.c
        objects.c
        get_next_line.h
        get_next_line_utils.c
        math_utils.c
        miniRT.c
        minirt.h
        parser.c
        color_utils.c
        cam_utils.c
        put.c
        libft/libft.h)


target_link_libraries(miniRT /Users/dmarget/miniRT/libft/libft.a
        /Users/dmarget/miniRT/mlx/libmlx.a)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -framework OpenGL -framework Appkit")