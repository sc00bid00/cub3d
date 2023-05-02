# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 09:54:24 by lsordo            #+#    #+#              #
#    Updated: 2023/05/02 15:32:15 by kczichow         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
FFLAGS = -framework Cocoa -framework OpenGL -framework IOKit
SRC_DIR = ./src/
OBJ_DIR = ./obj/
LIB_DIR = ./lib/

URL_LIBFT = https://github.com/Kathinka42/42_libft
URL_GLFW = https://github.com/glfw/glfw
URL_MLX42 = https://github.com/codam-coding-college/MLX42

LIBFT = $(LIB_DIR)libft
LIBFT_LNK = -l ft -L $(LIBFT)

LIBGLFW_LNK = -l glfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

LIBMLX	= $(LIB_DIR)MLX42
LIBMLX_LNK = -l mlx42 -L $(LIBMLX)/build

INC_DIR =	-I ./inc \
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

$(LIBGLFW):
	brew install glfw

$(LIBMLX):
	git clone $(URL_MLX42) $(LIBMLX)
	cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

.PHONY: all clean fclean re


