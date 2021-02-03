# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmarget <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/30 16:02:42 by dmarget           #+#    #+#              #
#    Updated: 2020/11/07 13:25:57 by dmarget          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= libft.a

SRCS 	= ft_isascii.c ft_memchr.c ft_strchr.c ft_strncmp.c \
ft_atoi.c ft_isdigit.c ft_memcmp.c ft_strdup.c ft_strnstr.c \
ft_bzero.c ft_isalnum.c ft_memcpy.c ft_strlcat.c ft_strrchr.c \
ft_calloc.c ft_isprint.c ft_memmove.c ft_strlcpy.c ft_tolower.c \
ft_isalpha.c ft_memccpy.c ft_memset.c ft_strlen.c ft_toupper.c  \
ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c \
ft_substr.c ft_strjoin.c ft_strtrim.c ft_itoa.c ft_strmapi.c ft_split.c \
ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_atof.c

OBJS	= ${SRCS:.c=.o}

GCC		= gcc

RM		= rm -f

LIB		= ar rc libft.a

CFLAGS	= -Wall -Wextra -Werror -c

.c.o:
			${GCC} ${CFLAGS} -I -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			${LIB} ${OBJS}

all: 		${NAME}

clean:
				${RM} ${OBJS} 

fclean:		clean
				${RM} ${NAME}

bonus:		all

re:			fclean all

so:			$(OBJS)
			gcc -o libft.so $(OBJS) -shared

.PHONY:		all clean fclean re
