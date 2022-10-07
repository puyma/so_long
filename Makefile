# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/27 13:10:44 by mpuig-ma          #+#    #+#              #
#    Updated: 2022/10/07 21:53:56 by mpuig-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= so_long
AUTHOR		?= mpuig-ma

CC			:= gcc
CFLAGS		:= -Wall -Werror -Wextra #-MMD
_FRAMEWORK	:= -framework OpenGL -framework AppKit
RM			:= rm -rf
SRC_DIR		:= src
BUILD_DIR	:= build

SRC_FILES	:= src/ft_so_long.c

# Color codes

NOCOLOR		:= \033[0m
GREEN		:= \033[0;32m
PURPLE		:= \033[1;35m
TERM_COLORS	:= $(shell tput colors)

# Color codes (improved) for 256 terminals

ifeq ($(TERM_COLORS), 256)
	GREEN	:= \033[0;38;5;82m
	PURPLE	:= \033[1;38;5;135m
endif

.PHONY: all fclean clean re run

all: $(NAME)

$(NAME)::
	@echo "Initializing $(PURPLE)so_long...$(NOCOLOR)"

$(NAME):: make_libraries
	@$(CC) $(FLAGS) $(_FRAMEWORK) $(SRC_FILES) libft/libft.a -o $(NAME)

$(NAME)::
	@echo "$(GREEN)Done!$(NOCOLOR)"

make_libraries::
	@echo ""

make_libraries::
	@make -sC libft
	@make -sC src/minilibx*

make_libraries::
	@echo "$(GREEN)Linked $(NOCOLOR)minilibx_mms_20210621"

clean:
	@$(RM) $(BUILD_DIR)

fclean: clean
	@$(RM) $(NAME)
	@make fclean -sC libft
	@make clean -sC src/minilibx*

re: fclean
	$(MAKE)
