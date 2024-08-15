# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: s.veselova <s.veselova@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/15 18:38:02 by aarponen          #+#    #+#              #
#    Updated: 2024/08/15 21:47:34 by s.veselova       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#detect OS
UNAME_S := $(shell uname -s)

# Compiler and compiler flags
CC = cc
CFLAGS = -Wall -Werror -Wextra -O3 -g

# MiniLibX library flags
ifeq ($(UNAME_S),Linux)
    MLX_PATH = ./minilibx-linux
    MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11
	CLEAN_UP_FILE = src/clean_up.c
	HOOKS = src/hooks.c
else ifeq ($(UNAME_S),Darwin)
    MLX_PATH = ./minilibx_opengl_20191021
    MLX_FLAGS = -L$(MLX_PATH) -lmlx -framework OpenGL -framework AppKit
    MLX_DOWNLOAD = curl -O https://cdn.intra.42.fr/document/document/27026/minilibx_opengl.tgz && tar -xzf minilibx_opengl.tgz && rm minilibx_opengl.tgz
	CLEAN_UP_FILE = src/clean_up_mac.c
	HOOKS = src/hooks_mac.c
endif

# Libft library flags
LIBFT_PATH = ./Libft
LIBFT_FLAGS = -L$(LIBFT_PATH) -lft

# Source and object files
SRC = src/main.c src/init.c src/launch.c \
	src/error_handling.c \
	src/parsing/parse.c  src/parsing/parse_ambient.c src/parsing/parse_camera.c \
	src/parsing/parse_light.c src/parsing/parse_sphere.c src/parsing/parse_plane.c \
	src/parsing/parse_cylinder.c src/parsing/parse_utils.c \
	src/draw/draw.c src/draw/draw_sphere.c src/draw/lighting.c \
	src/draw/draw_utils.c src/draw/vector_operations2.c \
	src/draw/camera_setup.c src/draw/vector_operations.c \
	src/draw/draw_plane.c src/draw/draw_cylinder.c  src/draw/draw_cylinder2.c \
	src/draw/color.c \
	src/utils.c $(HOOKS) $(CLEAN_UP_FILE)
OBJ = $(SRC:.c=.o)

# Header files
HDR = includes/minirt.h

# Executable name
NAME = miniRT

# Default rule
all: mlx libft $(NAME)

# Rule to compile MiniLibX
mlx:
ifeq ($(UNAME_S),Darwin)
	@if [ ! -d "$(MLX_PATH)" ]; then \
		echo "Downloading minilibx for macOS..."; \
		$(MLX_DOWNLOAD); \
	fi
endif
	make -C $(MLX_PATH)

# Rule to compile Libft
libft:
	make -C $(LIBFT_PATH)

# Rule to compile source files into object files
%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -I./includes -I$(MLX_PATH) -I$(LIBFT_PATH) -c $< -o $@

# Rule to link object files into executable
$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_FLAGS) $(LIBFT_FLAGS) -lm -o $(NAME)

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

.PHONY: all mlx libft clean fclean re