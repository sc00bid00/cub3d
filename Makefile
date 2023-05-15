# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 09:54:24 by lsordo            #+#    #+#              #
#    Updated: 2023/05/12 07:03:30 by lsordo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wextra -Wall -Werror -Wunreachable-code -Ofast -g -MMD
FFLAGS = -framework Cocoa -framework OpenGL -framework IOKit
SRC_DIR = ./src/
OBJ_DIR = ./obj/
LIB_DIR = ./lib/

# ====== SRC FILES ======
SRC =	utils_debug.c \
		utils_parse.c
# =======================

BRED	=	\033[1;31m
BGREEN	=	\033[1;32m
BYELLOW	=	\033[1;33m
BBLUE	=	\033[1;34m
WHITE	=	\033[0m

COLOR_MAKE = $(BGREEN)
COLOR_INSTALL = $(BYELLOW)
COLOR_CLEAN = $(BRED)
COLOR_CHECK = $(BBLUE)
DEFCL = $(WHITE)


# ====== SRC FILES ======
SRC =	main.c \
		memory_management.c \
		draw_line_bresenham.c \
		rays2d.c \
		scene.c
# =======================

BRED	=	\033[1;31m
BGREEN	=	\033[1;32m
BYELLOW	=	\033[1;33m
BBLUE	=	\033[1;34m
WHITE	=	\033[0m

COLOR_MAKE = $(BGREEN)
COLOR_INSTALL = $(BYELLOW)
COLOR_CLEAN = $(BRED)
COLOR_CHECK = $(BBLUE)
DEFCL = $(WHITE)

BREW = /Users/$(USER)/.brew/
HOMEBREW = /Users/$(USER)/homebrew/

URL_LIBFT = https://github.com/Kathinka42/42_libft
URL_MLX42 = https://github.com/codam-coding-college/MLX42

LIBFT = $(LIB_DIR)libft
LIBFT_LNK = -l ft -L $(LIBFT)

LIBGLFW_SCHOOL = "/Users/$(USER)/.brew/opt/glfw"
LIBGLFW_OTHER = "/usr/local/opt/glfw"
ifeq ($(shell test -d $(LIBGLFW_OTHER) && echo exists), exists)
	LIBGLFW = $(LIBGLFW_OTHER)
else
	LIBGLFW = $(LIBGLFW_SCHOOL)/lib
endif
LIBGLFW_LNK = -l glfw -L$(LIBGLFW)
GLFW_INC = $(LIBGLFW)/include/GLFW

LIBMLX	= $(LIB_DIR)MLX42
LIBMLX_LNK = -l mlx42 -L $(LIBMLX)/build
MLX_INC = $(LIBMLX)/include/MLX42

LSAN = $(LIB_DIR)LeakSanitizer
LSAN_LNK  =  -L $(LSAN) -llsan -lc++
LSAN_INC = -Wno-gnu-include-next -I lib/LeakSanitizer/include

OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)
DEP = $(SRC:%.c=$(OBJ_DIR)%.d)
INC_DIR =	-I ./inc -I $(LIBFT) -I $(MLX_INC) -I $(GLFW_INC)
LNK_DIR =	$(LIBFT_LNK) $(LIBMLX_LNK) $(LIBGLFW_LNK) $(FFLAGS)
DEPS = $(OBJ_DIR) $(LIBFT)/libft.a $(LIBMLX)/build/libmlx42.a $(LSAN)/liblsan.a $(OBJ)

all:	$(NAME)

lsan:	clean
lsan:	$(NAME) $(LSAN)
lsan:	INC_DIR += $(LSAN_INC)
lsan:	LNK_DIR += $(LSAN_LNK)
INC_DIR =	-I ./inc -I $(LIBFT) -I $(MLX_INC) -I $(GLFW_INC)
LNK_DIR =	$(LIBFT_LNK) $(LIBMLX_LNK) $(LIBGLFW_LNK) $(FFLAGS)
DEPS = $(OBJ_DIR) $(LIBFT)/libft.a $(LIBMLX)/build/libmlx42.a $(LSAN)/liblsan.a $(OBJ)

all:	$(NAME)

$(NAME): $(DEPS)
	@echo "$(COLOR_MAKE)Make cub3d ...$(DEFCL)"
	@$(CC) $(OBJ) -o $(NAME) $(LNK_DIR)

-include $(DEP)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) -c $(CFLAGS) $(INC_DIR) $< -o $@

$(OBJ_DIR):
	@mkdir -p ./obj

$(LIBFT)/libft.a:
ifneq ($(shell test -d $(LIBFT) && echo exists), exists)
	@echo "$(COLOR_INSTALL)Clone libft ...$(DEFCL)"
	@git clone -q --recurse-submodules $(URL_LIBFT) $(LIBFT)
endif
	@echo "$(COLOR_MAKE)Make libft ...$(DEFCL)"
	@$(MAKE) -s -C $(LIBFT)

$(LIBMLX)/build/libmlx42.a: $(BREW)
ifneq ($(shell test -d $(LIBGLFW) && echo exists), exists)
		@echo "$(COLOR_INSTALL)Install glfw ...$(DEFCL)"
		@brew install -q glfw
endif
ifneq ($(shell test -d $(LIBMLX) && echo exists), exists)
	@echo "$(COLOR_INSTALL)Clone MLX42 (> logscmake) ...$(DEFCL)"
	@git clone -q $(URL_MLX42) $(LIBMLX)
	@cmake -H$(LIBMLX) -B $(LIBMLX)/build > logscmake 2>&1
endif
	@echo "$(COLOR_MAKE)Make MLX42 (> logsbuild) ...$(DEFCL)"
	@$(MAKE) -s -C $(LIBMLX)/build -j4 > logsbuild 2>&1

$(BREW):
ifneq ($(shell test -f "/usr/local/bin/brew" && echo exists), exists)
	@echo "$(COLOR_INSTALL)Install brew ...$(DEFCL)"
	@/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
endif

$(LSAN)/liblsan.a:
ifneq ($(shell test -d $(LSAN) && echo exists), exists)
	@echo "$(COLOR_INSTALL)Clone LeakSanitizer ...$(DEFCL)"
	@git clone -q --recursive https://www.github.com/mhahnFr/LeakSanitizer.git ./lib/LeakSanitizer/
endif
	@echo "$(COLOR_MAKE)Make LeakSanitizer (> logslsan) ...$(DEFCL)"
	@$(MAKE) -s -C ./lib/LeakSanitizer 2>logslsan

clean:
	@echo "$(BRED)Remove objs ...$(DEFCL)"
	@rm -rf $(OBJ_DIR) $(LIB)
	@echo "$(BRED)Clean libs ...$(DEFCL)"
	@$(MAKE) clean -s -C  $(LIBFT)
	@$(MAKE) clean -s -C $(LSAN)

fclean:	clean
	@echo "$(BRED)Remove exec ...$(DEFCL)"
	@rm -rf $(NAME)
	@echo "$(BRED)Remove libs ...$(DEFCL)"
	@$(MAKE) clean -s -C $(LIBMLX)/build
	@$(MAKE) fclean -s -C $(LIBFT)
	@$(MAKE) fclean -s -C $(LSAN)
	@echo "$(BRED)Remove logs ...$(DEFCL)"
	@rm -f logsbuild logscmake logslsan


re: fclean all

.PHONY: all clean fclean re
