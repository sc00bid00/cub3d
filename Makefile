# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 09:54:24 by lsordo            #+#    #+#              #
#    Updated: 2023/05/02 13:48:37 by lsordo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Ofast
FFLAGS = -framework Cocoa -framework OpenGL -framework IOKit
SRC_DIR = ./src/
OBJ_DIR = ./obj/
LIB_DIR = ./lib/

URL_LIBFT = https://github.com/Kathinka42/42_libft
URL_GLFW = https://github.com/glfw/glfw
URL_MLX42 = https://github.com/codam-coding-college/MLX42

LIBFT = $(LIB_DIR)libft
LIBFT_LNK = -l ft -L $(LIBFT)

LIBGLFW = $(LIB_DIR)glfw
LIBGLFW_LNK = -l glfw -L $(LIBGLFW)

LIBMLX42 = $(LIB_DIR)MLX42
LIBMLX42_LNK = -l mlx42 -L $(LIBMLX42)

INC_DIR =	-I ./include \
			-I ./lib/libft \
			-I ./lib/glfw/glfw-3.3.8.bin.MACOS/include/GLFW \
			-I ./lib/MLX42/include/MLX42

SRC =	main.c

OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJ_DIR) $(LIBFT) $(LIBGLFW) $(LIBMLX42) $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) $(LIBFT_LNK) $(LIBGLFW_LNK) $(LIBMLX42_LNK)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) -c $(CFLAGS) $(INC_DIR) $^ -o $@

$(OBJ_DIR):
	@mkdir -p ./obj

$(LIBFT):
	git clone --recurse-submodules $(URL_LIBFT) $(LIBFT)
	$(MAKE) -C $(LIBFT)

$(LIBGLFW):
	git clone $(URL_GLFW) $(LIBGLFW)
	cmake -H$(LIBGLFW) -B $(LIBGLFW)/build
	cmake --build $(LIBGLFW)/build -j4

$(LIBMLX42):
	git clone $(URL_MLX42) $(LIBMLX42)
	cmake -H$(LIBMLX42) -B $(LIBMLX42)/build
	cmake --build $(LIBMLX42)/build -j4

.PHONY: all clean fclean re


