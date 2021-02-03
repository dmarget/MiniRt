# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmarget <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/11 17:26:38 by dmarget           #+#    #+#              #
#    Updated: 2020/12/11 17:26:42 by dmarget          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a

CC		=	gcc

FLAG	=	-Wall -Wextra -Werror

RM		=	rm -f

AR		=	ar rc

SRC_P	=	./processor/

SRC_U	=	./utils/

INC_D	=	./include/

INC		=	ft_printf.h

SRCS	=	ft_printf.c ft_parser.c \
			$(addprefix ${SRC_U}, ft_atoi.c ft_printf_utils.c second_utils.c ) \
			$(addprefix ${SRC_P}, valid.c print_chr.c print_int.c \
			print_per.c print_p.c print_str.c print_u.c \
			print_hex.c print_cap_hex.c )

OBJS	=	${SRCS:.c=.o}

all:		$(NAME)

${NAME}: ${OBJS} ${INC_D}${INC}
	${AR} ${NAME} ${OBJS}


%.o: %.c ${INC_D}${INC}
	${CC} ${FLAG} -I ${INC_D} -c $< -o $@

clean:		
	rm -f ${OBJS}

fclean:		clean
	rm -f ${NAME}

re:     fclean all











# NAME	=	libftprintf.a

# SRCS	=	ft_init.c ft_reinit.c ft_printf.c ft_printf_utils.c ft_parser.c \
# 			display_int.c display_chr.c display_str.c display_pointer.c \
# 			display_x.c display_u.c display_x_cap.c display_percent.c \
# 			ft_atoi.c ft_strlen.c check_ft.c ft_putstr.c

# OBJS	=	$(SRCS:.c=.o)

# GCC		=	gcc

# RM		=	rm -f

# AR		=	ar rcs

# FLAG	=	-Wall -Werror -Wextra

# all:		$(NAME)

# .c.o:
# 			$(GCC) $(FLAG) -c $< -o $(<:.c=.o)

# $(NAME):	$(OBJS)
# 			$(AR) $(NAME) $(OBJS)
# 	#		$(GCC) $(FLAG) $(SRCS)

# clean:
# 			$(RM) $(OBJS)

# fclean:		clean
# 			$(RM) $(NAME)

# re:			fclean $(NAME)

# .PHONY:		all clean fclean re
