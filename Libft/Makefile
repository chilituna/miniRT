# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/06 13:05:20 by aarponen          #+#    #+#              #
#    Updated: 2024/07/21 12:46:37 by aarponen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Werror -Wextra

CC = cc -include libft.h

HEADER = libft.h

SRC_FILES = ft_isdigit.c ft_putnbr_fd.c ft_bzero.c ft_split.c ft_tolower.c \
	ft_substr.c ft_isprint.c ft_strchr.c ft_memcmp.c ft_strtrim.c ft_strdup.c \
	ft_toupper.c ft_putendl_fd.c ft_strmapi.c ft_strjoin.c ft_strnstr.c \
	ft_putchar_fd.c ft_isascii.c ft_striteri.c ft_memcpy.c ft_itoa.c \
	ft_strlen.c ft_isalpha.c ft_strlcat.c ft_strrchr.c ft_putstr_fd.c \
	ft_isalnum.c ft_memchr.c ft_memmove.c ft_strncmp.c ft_atoi.c ft_strlcpy.c \
	ft_memset.c ft_calloc.c ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c  ft_lstiter_bonus.c ft_lstmap_bonus.c ft_printf.c \
	ft_puthex.c ft_putnumber.c ft_putpointer.c ft_puttext.c ft_atod.c ft_atol.c \
	get_next_line.c ft_iswhitespace.c ft_atof.c

OBJ_FILES = $(SRC_FILES:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ_FILES)
	ar rcs $(NAME) $(OBJ_FILES)

$(OBJ_FILES): %.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

