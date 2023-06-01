Name :=	cub3D

OS	:= $(shell uname)
#Compiler
CC :=	cc
CFLAGS	:=	-Wall -Wextra -Werror
CFLAGS	+= -O2 -MMD
#CFLAGS	+=	-g -fsanitize=address

#Interplatform compatibility
# ifeq ($(OS), Darwin)
# 	ifneq ($(shell which brew && echo true), true)
# 		@echo "$(COLOR_INSTALL)Install brew ...$(DEFCL)"
# 		@/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
# 	endif
# 	ifneq ($(shell which cmake && echo true), true)
# 		@echo "$(COLOR_INSTALL)Install cmake ...$(DEFCL)"
# 		@brew install -q cmake
# 	endif
# else ifeq ($(OS), Linux)
# 	ifneq ($(shell which cmake && echo true), true)
# 		@echo "$(COLOR_INSTALL)Install cmake ...$(DEFCL)"
# 		@apt update
# 		@apt -qq -y install cmake
# 	endif
# endif

#Inputsources
VPATH	:= ./src

SRC_F	:=	main.c \
			setup.c \
			memory_management.c \
			draw.c \
			hooks.c \
			rendering.c \
			scene.c \
			minimap.c \
			parse_1_init_check.c \
			parse_2_getdata.c \
			parse_3_gettable.c \
			parse_4_playerdata.c \
			parse_5_colors_textures.c \
			parse_6_other_check.c \
			texture.c \
			utils_debug.c \
			window.c \
			rays.c

#Headers
INC_D	:= ./inc
INC_F	:= -I $(INC_D) -I $(LIBFT_D) -I $(MLX42_D)/include/MLX42


#Libraries
LIBFT_D := ./lib/libft
LIBFT_F := $(LIBFT_D)/libft.a
MLX42_D	:=	./lib/MLX42/build
MLX42_F	:=	$(MLX42_D)/libmlx42.a
LIB		:= -L $(LIBFT_D) -l ft -L $(MLX42_D) -l mlx42 -l glfw
ifeq ($(OS), Linux)
	LIB	+= -lm -ldl
endif

#Object Dependencies
OBJ_D :=	./build
OBJ_F	:= $(patsubst %.c,$(OBJ_D)/%.o,$(SRC_F))
DEP_F	:= $(patsubst %.c,$(OBJ_D)/%.d,$(SRC_F))

#Rules
all:
	$(MAKE) $(NAME) -j

$(NAME): $(LIBFT_F) $(MLX42_F) $(OBJ_D) $(OBJ_F)
	$(CC) $(CFLAGS) $(INC_F) -o $(NAME) $(OBJ_F) $(LIB)

$(OBJ_D)/%.o: %.c
	$(CC) $(CFLAGS) $(INC_F) -c $< -o $@

-include $(DEP_F)

$(OBJ_D):
	mkdir -p $@

$(LIBFT_F):
	make -j -C $(LIBFT_D)

$(MLX42_F):
	make -j -C $(MLX42_D)

clean:

fclean: clean

re:

.PHONY: all fclean clean re
