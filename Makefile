# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/01 19:36:25 by tonted            #+#    #+#              #
#    Updated: 2023/02/18 10:57:30 by pirichar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Configuration of paths
SRCDIR		= src
OBJDIR		= obj
INCDIR		= include

# Libft
LIBFTDIR	= libraries/libft
LIBFTLIB	= -L$(LIBFTDIR) -lft

# mlx
MLXDIR		= libraries/MLX42
MLXLIB		= -L$(MLXDIR) -lmlx42 -lglfw -L /Users/${USER}/.brew/Cellar/glfw/3.3.8/lib/ -framework OpenGL -framework AppKit
#MLXLIB		= -L$(MLXDIR) -lmlx42 -lglfw -L /opt/homebrew/Cellar/glfw/3.3.8/lib/ -framework OpenGL -framework AppKit

# Name of the final executable
NAME = cub3d

# Decide whether the commands will be shown or not
VERBOSE = TRUE

# Unit Test management
UTEST = .test/_test_main.c
USRCS = $(wildcard .test/*.c)

# Create the list of directories
DIRS = $(shell find $(SRCDIR) -type d | sed 's/$(SRCDIR)\///g' | sed -n '1!p')
SRCDIRS	= $(foreach dir, $(DIRS), $(addprefix $(SRCDIR)/, $(dir)))
OBJDIRS = $(foreach dir, $(DIRS), $(addprefix $(OBJDIR)/, $(dir)))

# Create a list of *.c sources in DIRS
SRCS = $(wildcard src/*.c)
SRCS += $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))
# SRCS := $(filter-out $(ENTRYPOINT), $(SRCS))

# Define objects for all sources
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

# Name the compiler & flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

BONUS = false


$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(HIDE)$(CC) $(CFLAGS) -iquote$(INCDIR) -iquote$(LIBFTDIR) -D BONUS=$(BONUS) -c  $< -o $@

all			: buildrepo $(NAME)

$(NAME)		: $(OBJS)
	$(MAKE) -C $(LIBFTDIR)
	$(MAKE) -C $(MLXDIR)
	$(HIDE)$(CC) $(CFLAGS) $(OBJS) $(LIBFTLIB) $(MLXLIB) -o $(NAME)
	@printf $(GREEN)"[$@] program created\n"$(RESET)

clean		:
	$(HIDE)rm -rf $(OBJDIR)
	$(HIDE)$(MAKE) clean -C $(LIBFTDIR)
	$(HIDE)rm -rf $(MLXDIR)/*.o
	@printf $(YELLOW)"[$(NAME)] objects removed\n"$(RESET)

fclean		: clean
	$(HIDE)rm -f $(NAME)
	$(HIDE)rm -f $(MLXDIR)/libmlx.a
	$(HIDE)$(MAKE) fclean -C $(LIBFTDIR)

bonus		:  setBonus all

re			:
	$(HIDE)rm -rf $(OBJDIR)
	$(HIDE)rm -f $(NAME)
	$(HIDE)make
	
buildrepo	:
	$(HIDE)$(call make-repo)

setBonus	:
	$(eval BONUS := true)

print	:
	@echo $(DIRS)
	@echo $(SRCS)

# VALGRIND = -
# VALGRIND = -valgrind --leak-check=yes
VALGRIND = -leaks --atExit --

test0	: all
	$(VALGRIND) ./so_long maps/map0.ber
test1	: all
	$(VALGRIND) ./so_long maps/map1.ber
test2	: all
	$(VALGRIND) ./so_long maps/map_smaller.ber
teste	: all
	$(VALGRIND) ./so_long maps/map_enemy.ber
test_err	: all
	$(VALGRIND) ./so_long maps/map_err_exit0.ber
	$(VALGRIND) ./so_long maps/map_err_exit2.ber
	$(VALGRIND) ./so_long maps/map_err_player0.ber
	$(VALGRIND) ./so_long maps/map_err_player2.ber
	$(VALGRIND) ./so_long maps/map_err_open.ber
	$(VALGRIND) ./so_long maps/map_not_rect.ber
	@chmod 111 maps/map_err_file.ber
	$(VALGRIND) ./so_long maps/map_err_file.ber
	@chmod 777 maps/map_err_file.ber

_test	:  all
	 ./so_long

docker		:
	docker build ../ -t 42/valgrind
	docker run --rm -it --name valgrind -v /Users/tonted/42:/42projects 42/valgrind

.PHONY		: clean fclean all re $(OBJDIR) buildrepo print

# Create 
define make-repo
	$(HIDE)mkdir -p $(OBJDIR)
	$(HIDE)for dir in $(DIRS); \
   	do \
	$(HIDE)mkdir -p $(OBJDIR)/$$dir; \
   	done
endef

# Color
BLACK := "\e[0;30m"
RED := "\e[0;31m"
GREEN := "\e[0;32m"
YELLOW := "\e[0;33m"
BLUE := "\e[0;34m"
MAGENTA := "\e[0;35m"
CYAN := "\e[0;36m"
RESET :="\e[0m"

# Hide or not the calls depending of VERBOSE
ifeq ($(VERBOSE),TRUE)
    HIDE =  
else
    HIDE = @
endif

# src/clean_exit.c src/main.c src/bonus/bonus_hook.c src/bonus/collision_bonus.c src/bonus/draw_bonus.c src/bonus/init_bonus.c src/bonus/minimap/draw_minimap.c src/bonus/minimap/minimap_background.c src/hooks/hook_keyboard.c src/init/init.c src/init/init_map.c src/init/is_map_closed.c src/main_window/draw_main_window.c src/main_window/get_ray_length.c src/main_window/utils_main_windows.c src/parsing/parse_file.c src/parsing/parse_map.c src/parsing/parse_textures.c src/utils/draw_utils.c src/utils/gnl.c src/utils/tabstr_utils.c src/utils/utils.c src/utils/utils_image.c