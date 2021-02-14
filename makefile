NAME    =   miniRT
LIBFT   =   libft.a
LIBMLX  =   libmlx.dylib
SRC     :=  $(addprefix srcs/,      \
            bmp.c                  \
            cam_utils.c               \
            check.c   \
            color_utils.c           \
            cylindr.c         \
            ft_atof.c                \
            ft_atoi.c    \
            ft_ssplit.c   \
            get_next_line.c        \
            get_next_line_utils.c        \
            math_utils.c         \
            math_utils_two.c \
            normal_utils.c      \
            objects.c         \
            parser.c      \
            put.c	\
            parse_utils.c \
            utils_two.c\
            minirt.c\
            ft_split_rt.c \
            put_utils.c\
            parse_obj.c)
HEADER =  include/minirt.h

OBJ     =   $(SRC:.c=.o)
OBJ     =   $(SRC:.c=.o)
CC      =   gcc -Iincludes -Imlx -Ilibft
.PHONY:     all clean fclean re
all:        $(NAME)
%.o:        %.c $(HEADER)
libft/libft.a:
	$(MAKE) -C libft
$(LIBMLX):
	$(MAKE) -C mlx
$(NAME):    $(OBJ) mlx libft/libft.a
			$(CC) -Llibft -lft -Lmlx -lmlx -framework OpenGL \
                -framework AppKit -o $(NAME) $(OBJ) libft/$(LIBFT) $(LIBMLX)
clean:
	-rm -f $(OBJ)
fclean:     clean
	make -C ./libft fclean
	-rm -f $(NAME)
	-rm -f *.bmp
re:         fclean all
