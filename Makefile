# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 09:54:24 by lsordo            #+#    #+#              #
#    Updated: 2023/05/05 11:00:49 by kczichow         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#COLORS-----------------------------------------------------------------------#
BRED	=	\033[1;31m
BGREEN	=	\033[1;32m
BYELLOW	=	\033[1;33m
BLUE	=	\033[1;34m
WHITE	=	\033[0m
#-----------------------------------------------------------------------------#

COLOR_MAKE = $(BGREEN)
COLOR_INSTALL = $(BYELLOW)
COLOR_CLEAN = $(BRED)
DEFCL = $(WHITE)

NAME = cub3D
CC = cc
#CFLAGS = -Wextra -Wall -Werror -Wunreachable-code -Ofast
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

LIBGLFW_LNK = -l glfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

LIBMLX	= $(LIB_DIR)MLX42
LIBMLX_LNK = -l mlx42 -L $(LIBMLX)/build

INC_DIR =	-I ./inc \
			-I ./lib/libft \
			-I ./lib/MLX42/include/MLX42

SRC =	main.c \
		memory_management.c

OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJ_DIR) $(LIBFT) $(LIBGLFW) $(LIBMLX) $(OBJ)
	@echo "$(COLOR_MAKE)Make cub3d...$(DEFCL)"
	@$(CC) $(OBJ) -o $(NAME) $(LIBFT_LNK) $(LIBMLX_LNK) $(LIBGLFW_LNK) $(FFLAGS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) -c $(CFLAGS) $(INC_DIR) $^ -o $@

$(OBJ_DIR):
	@mkdir -p ./obj

$(LIBFT):
	@echo "$(COLOR_INSTALL)Clone libft...$(DEFCL)"
	@git clone -q --recurse-submodules $(URL_LIBFT) $(LIBFT)
	@echo "$(COLOR_MAKE)Make libft...$(DEFCL)"
	@$(MAKE) -s -C $(LIBFT)

$(LIBGLFW): $(BREW)
	@echo "$(COLOR_INSTALL)Install glfw...$(DEFCL)"
	@brew install -q glfw

$(LIBMLX):
	@echo "$(COLOR_INSTALL)Install MLX42...$(DEFCL)"
	@git clone -q $(URL_MLX42) $(LIBMLX)
	@echo "$(COLOR_MAKE)Make MLX42...$(DEFCL)"
	@cmake -H$(LIBMLX) -B $(LIBMLX)/build
	@make -s -C $(LIBMLX)/build -j4

$(BREW):
	@echo "$(COLOR_INSTALL)Install brew...$(DEFCL)"
	@/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

clean:
	@echo "$(BRED)Clean objects...$(DEFCL)"
	@rm -rf $(OBJ_DIR)
	@echo "$(BRED)Clean libft...$(DEFCL)"
	@make clean -s -C $(LIBFT)
	@echo "$(BRED)Clean MLX42...$(DEFCL)"
	@make clean -s -C $(LIBMLX)/build

fclean: clean
	@echo "$(BRED)Clean exec...$(DEFCL)"
	@rm -f $(NAME)
	@echo "$(BRED)Remove lib...$(DEFCL)"
	@rm -rf $(LIB_DIR)

re: fclean all

.PHONY: all clean fclean re
