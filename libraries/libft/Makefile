# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/26 11:20:34 by tblanco           #+#    #+#              #
#    Updated: 2021/12/16 14:50:21 by tblanco          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Configuration of paths
SRCDIR := src
OBJDIR := obj
INCDIR := include

# Name of the final executable
NAME = libft.a

# Decide whether the commands will be shwon or not
VERBOSE = FALSE

# Create the list of directories
DIRS = $(shell find $(SRCDIR) -type d | sed 's/$(SRCDIR)\///g' | sed -n '1!p')
SRCDIRS	= $(foreach dir, $(DIRS), $(addprefix $(SRCDIR)/, $(dir)))
OBJDIRS = $(foreach dir, $(DIRS), $(addprefix $(OBJDIR)/, $(dir)))

# Create a list of *.c sources in DIRS
SRCS = $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.c))

# Define objects for all sources
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

# Name the compiler & flags
CC = clang
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -iquote$(INCDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(HIDE)$(CC) $(CFLAGS) -c  $< -o $@

all			: buildrepo $(NAME)

$(NAME)		: $(OBJS)
	$(HIDE)ar rc $@ $(OBJS)
	$(HIDE)ranlib $@
	@printf $(GREEN)"[$@] lib created\n"$(RESET)
	
clean		:
	$(HIDE)rm -rf $(OBJDIR)
	@printf $(YELLOW)"[$(NAME)] objects removed\n"$(RESET)


fclean		: clean
	$(HIDE)rm -f $(NAME)
	@printf $(YELLOW)"[$(NAME)] lib removed\n"$(RESET)

buildrepo	:
	$(HIDE)$(call make-repo)

print	:
	@echo $(DIRS)
	@echo $(SRCS)

.PHONY		: clean fclean all re $(OBJDIR) buildrepo print

# Create 
define make-repo
   for dir in $(DIRS); \
   do \
	mkdir -p $(OBJDIR)/$$dir; \
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

# List of files:
# src/checker/ft_isalnum.c src/checker/ft_isalpha.c src/checker/ft_isascii.c src/checker/ft_ischarinstr.c src/checker/ft_isdigit.c src/checker/ft_isprint.c src/checker/ft_issetinstr.c src/comparator/ft_bigger.c src/comparator/ft_lower.c src/converter/ft_atoi.c src/converter/ft_itoa.c src/list/ft_lstadd_back.c src/list/ft_lstadd_front.c src/list/ft_lstclear.c src/list/ft_lstdelone.c src/list/ft_lstiter.c src/list/ft_lstlast.c src/list/ft_lstmap.c src/list/ft_lstnew.c src/list/ft_lstsize.c src/memory/ft_bzero.c src/memory/ft_calloc.c src/memory/ft_memchr.c src/memory/ft_memcmp.c src/memory/ft_memcpy.c src/memory/ft_memmove.c src/memory/ft_memset.c src/modifier/ft_tolower.c src/modifier/ft_toupper.c src/printer/ft_putchar_fd.c src/printer/ft_putendl_fd.c src/printer/ft_putnbr_fd.c src/printer/ft_putstr_fd.c src/string/ft_split.c src/string/ft_strchr.c src/string/ft_strdup.c src/string/ft_striteri.c src/string/ft_strjoin.c src/string/ft_strlcat.c src/string/ft_strlcpy.c src/string/ft_strlen.c src/string/ft_strmapi.c src/string/ft_strncmp.c src/string/ft_strnstr.c src/string/ft_strrchr.c src/string/ft_strtrim.c src/string/ft_substr.c