# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/27 13:10:44 by mpuig-ma          #+#    #+#              #
#    Updated: 2022/09/27 15:59:41 by mpuig-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= so_long
AUTHOR		?= mpuig-ma

CC			:= gcc
CFLAGS		:= -Wall -Werror -Wextra # -MMD
RM			:= rm -rf
SRC_DIR		:= src
BUILD_DIR	:= build

SRC_FILES	:= ...

# Color codes

NOCOLOR		:= \033[0m
GREEN		:= \033[0;32m

.PHONY: all fclean clean re

all: $(NAME)

$(NAME)::
	@echo "Ini...$(NOCOLOR)"

$(NAME)::
	@echo "$(GREEN)Done!$(NOCOLOR)"

clean:
	@$(RM) $(BUILD_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean
	$(MAKE)
