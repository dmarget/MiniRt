cmake_minimum_required(VERSION 3.17)
project(miniRT C)

set(CMAKE_C_STANDARD 99)

include_directories(includes)
add_executable(miniRT
        srcs/ft_ssplit.c
        srcs/cylindr.c
        srcs/normal_utils.c
        srcs/get_next_line.c
        srcs/objects.c
        srcs/check.c
        srcs/ft_atoi.c
        srcs/get_next_line_utils.c
        srcs/math_utils.c
        srcs/bmp.c
        srcs/ft_atof.c
        includes/minirt.h
        srcs/parser.c
        srcs/color_utils.c
        srcs/cam_utils.c
        srcs/put.c
        includes/libft.h
        includes/get_next_line.h
        libmlx.dylib
        srcs/parse_utils.c
        srcs/parse_obj.c
        srcs/utils_two.c
        srcs/minirt.c
        srcs/put_utils.c
        )


#target_link_libraries(miniRT /Users/dmarget/miniRT/libft/libft.a
#        /Users/dmarget/miniRT/mlx/libmlx.a)
target_link_libraries(miniRT /Users/dmarget/miniRT/libft/libft.a
        /Users/dmarget/Downloads/miniRT-new/libmlx.dylib)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -framework OpenGL -framework Appkit")