# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/15 18:38:02 by aarponen          #+#    #+#              #
#    Updated: 2024/07/22 19:44:24 by aarponen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and compiler flags
CC = cc
CFLAGS = -Wall -Werror -Wextra -O3 -g

# MiniLibX library flags
MLX_PATH = ./minilibx-linux
MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11

# Libft library flags
LIBFT_PATH = ./Libft
LIBFT_FLAGS = -L$(LIBFT_PATH) -lft

# Source and object files
SRC = src/main.c src/init.c src/parse.c src/launch.c \
	src/clean_up.c src/error_handling.c \
	src/parse_ambient.c src/parse_camera.c src/parse_light.c \
	src/utils.c src/hooks.c
OBJ = $(SRC:.c=.o)

# Header files
HDR = includes/minirt.h

# Executable name
NAME = minirt

# Default rule
all: mlx libft $(NAME)

# Rule to compile MiniLibX
mlx:
	make -C $(MLX_PATH)

# Rule to compile Libft
libft:
	make -C $(LIBFT_PATH)

# Rule to compile source files into object files
%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -I./includes -I$(MLX_PATH) -I$(LIBFT_PATH) -c $< -o $@

# Rule to link object files into executable
$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_FLAGS) $(LIBFT_FLAGS) -o $(NAME)

# Rule to clean up object files
clean:
	rm -f $(OBJ)
	make -C $(MLX_PATH) clean
	make -C $(LIBFT_PATH) clean

# Rule to clean up everything
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean

# Rule to re-make everything
re: fclean all
