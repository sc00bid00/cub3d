# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 09:54:24 by lsordo            #+#    #+#              #
#    Updated: 2023/05/02 15:24:44 by lsordo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
FFLAGS = -framework Cocoa -framework OpenGL -framework IOKit
SRC_DIR = ./src/
OBJ_DIR = ./obj/
LIB_DIR = ./lib/
BREW = /Users/$(USER)/.brew/
HOMEBREW = /Users/$(USER)/homebrew/

URL_LIBFT = https://github.com/Kathinka42/42_libft
URL_MLX42 = https://github.com/codam-coding-college/MLX42

LIBFT = $(LIB_DIR)libft
LIBFT_LNK = -l ft -L $(LIBFT)

LIBGLFW = "/Users/$(USER)/.brew/opt/glfw/lib"
LIBGLFW_LNK = -l glfw -L$(LIBGLFW)

LIBMLX	= $(LIB_DIR)MLX42
LIBMLX_LNK = -l mlx42 -L $(LIBMLX)/build

INC_DIR =	-I ./include \
			-I ./lib/libft \
			-I ./lib/MLX42/include/MLX42

SRC =	main.c

OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJ_DIR) $(LIBFT) $(LIBGLFW) $(LIBMLX) $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) $(LIBFT_LNK) $(LIBMLX_LNK) $(LIBGLFW_LNK) $(FFLAGS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) -c $(CFLAGS) $(INC_DIR) $^ -o $@

$(OBJ_DIR):
	@mkdir -p ./obj

$(LIBFT):
	git clone --recurse-submodules $(URL_LIBFT) $(LIBFT)
	$(MAKE) -C $(LIBFT)

$(LIBGLFW): $(BREW)
	brew install glfw

$(BREW):
	/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

$(LIBMLX):
	git clone $(URL_MLX42) $(LIBMLX)
	cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

.PHONY: all clean fclean re


