NAME =	cub3D
OS	= $(shell uname)

#Compiler
CC =	cc
CFLAGS	=	-Wall -Wextra -Werror #
CFLAGS	+=  -MMD
#CFLAGS	+=	-g -fsanitize=address

#Interplatform compatibility
ifeq ($(OS), Darwin)
ifeq ($(shell which brew), )
	@echo "$(COLOR_INSTALL)Install brew ...$(DEFCL)"
	@/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
	BREW_D := $(shell which brew | cut -d'/' -f1-4)
else
	BREW_D := $(shell which brew | cut -d'/' -f1-4)
endif
ifeq ($(shell which cmake), )
	@echo "$(COLOR_INSTALL)Install cmake ...$(DEFCL)"
	@brew install -q cmake
endif
else ifeq ($(OS), Linux)
ifeq ($(shell which cmake), )
	@echo "$(COLOR_INSTALL)Install cmake ...$(DEFCL)"
	@apt update
	@apt -qq -y install cmake
endif
endif

#Inputsources
VPATH	= 	./src

SRC_F	=	draw.c \
			hooks.c \
			main.c \
			memory_management.c \
			minimap.c \
			parse_1_init_check.c \
			parse_2_getdata.c \
			parse_3_gettable.c \
			parse_4_playerdata.c \
			parse_5_colors_textures.c \
			parse_6_other_check.c \
			rays.c \
			rendering.c \
			scene.c \
			setup.c \
			texture.c \
			utils_debug.c \
			window.c

#Libraries
LIBFT_D = ./lib/libft
LIBFT_F = $(LIBFT_D)/libft.a
LIBFT_URL = https://github.com/Kathinka42/42_libft
MLX42_D	=	./lib/MLX42
MLX42_BUILD_D = $(MLX42_D)/build
LSAN_D = ./lib/LeakSanitizer
LSAN_F = $(LSAN_D)/liblsan.a

MLX42_F	=	$(MLX42_BUILD_D)/libmlx42.a
MLX42_URL = https://github.com/codam-coding-college/MLX42
LIB	= -L $(LIBFT_D) -l ft -L $(MLX42_BUILD_D) -l mlx42 -L $(BREW_D)/opt/glfw/lib -l glfw
ifeq ($(OS), Linux)
	LIB	+= -lm -ldl
endif

#Headers
INC_D	= ./inc
INC_F	= -I $(INC_D) -I $(LIBFT_D) -I $(MLX42_D)/include/MLX42
ifeq ($(OS), Darwin)
ifeq ($(shell test -d $(LSAN_D) && test -f $(LSAN_F) && echo exists), exists)
	INC_F +=  -Wno-gnu-include-next -I $(LSAN_D)/include
	LIB += -L $(LSAN_D) -llsan -lc++
endif
else ifeq ($(OS), Linux)
ifeq ($(shell test -d $(LSAN_D) && test -f $(LSAN_F) && echo exists), exists)
	INC_F += -Wno-gnu-include-next -I $(LSAN_D)/include
	LIB += -rdynamic -L $(LSAN_D) -llsan -ldl -lstdc++
endif
endif
#Object Dependencies
OBJ_D	= ./obj
OBJ_F	= $(patsubst %.c,$(OBJ_D)/%.o,$(SRC_F))
DEP_F	= $(patsubst %.c,$(OBJ_D)/%.d,$(SRC_F))

#Rules
all: $(LIBFT_F) $(MLX42_F)
	@$(MAKE) -j $(NAME)

lsan: clean $(LIBFT_F) $(MLX42_F) $(LSAN_F)
	@$(MAKE) -j $(NAME)

$(NAME): $(OBJ_D) $(OBJ_F)
	$(CC) $(CFLAGS) $(INC_F) -o $(NAME) $(OBJ_F) $(LIB)

$(OBJ_D)/%.o: %.c
	$(CC) $(CFLAGS) $(INC_F) -c $< -o $@

-include $(DEP_F)

$(OBJ_D):
	mkdir -p $@

$(LIBFT_F):
ifneq ($(shell test -d $(LIBFT_D) && echo exists), exists)
	@echo "$(COLOR_INSTALL)Clone libft ...$(DEFCL)"
	@git clone -q --recurse-submodules $(LIBFT_URL) $(LIBFT_D)
endif
	$(MAKE) -j -C $(LIBFT_D)

$(MLX42_F):
ifneq ($(shell test -d $(MLX42_D) && echo exists), exists)
	@echo "$(COLOR_INSTALL)Clone MLX42 ...$(DEFCL)"
	@git clone -q --recurse-submodules $(MLX42_URL) $(MLX42_D)
endif
ifneq ($(shell test -d $(MLX42_BUILD_D) && echo exists), exists)
	@echo "$(COLOR_INSTALL)Cmake MLX42 ...$(DEFCL)"
	@cmake -H$(MLX42_D) -B $(MLX42_BUILD_D) > logscmake 2>&1
endif
	$(MAKE) -j -C $(MLX42_BUILD_D)

$(LSAN_F):
ifneq ($(shell test -d $(LSAN_D) && echo exists), exists)
	@echo "$(COLOR_INSTALL)Clone LeakSanitizer ...$(DEFCL)"
	@git clone -q --recursive https://www.github.com/mhahnFr/LeakSanitizer.git $(LSAN_D)
endif
	@echo "$(COLOR_MAKE)Make LeakSanitizer (> logslsan) ...$(DEFCL)"
	@$(MAKE) -s -C $(LSAN_D) 2>logslsan

clean:
	@echo "$(BRED)Remove objs ...$(DEFCL)"
	@rm -f $(LSAN_F)
	@rm -rf $(OBJ_D)

fclean: clean
	@$(MAKE) fclean -s -C $(LIBFT_D)
	@$(MAKE) fclean -s -C $(LSAN_D)
	@rm -f $(NAME)

re: fclean all


.PHONY: all fclean clean re lsan
