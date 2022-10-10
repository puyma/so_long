# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/27 13:10:44 by mpuig-ma          #+#    #+#              #
#    Updated: 2022/10/10 18:30:22 by mpuig-ma         ###   ########.fr        #
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

SRC_FILES	:= src/ft_so_long.c \
			   src/ft_launch.c \
			   src/ft_isextension.c \
			   src/ft_check_map.c 

# Color codes

NOCOLOR		:= \033[0m
GREEN		:= \033[0;32m
PURPLE		:= \033[1;35m
TERM_COLORS	:= $(shell tput colors)

# Color codes (improved) for 256 terminals

ifeq ($(TERM_COLORS), 256)
	PURPLE	:= \033[1;38;5;135m
endif

# .o to .c rule

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
	$(call msg,Compiled,$(notdir $<))

OBJS	= $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(notdir $(basename $(SRC_FILES)))))
DEPS	= $(addprefix $(BUILD_DIR)/, $(addsuffix .d, $(notdir $(basename $(SRC_FILES)))))

.PHONY: all make_libraries fclean clean re run norm

all: $(NAME)

$(NAME):: make_libraries $(OBJS)
	@$(CC) $(FLAGS) $(_FRAMEWORK) $(SRC_FILES) libft/libft.a -o $(NAME)

$(NAME)::
	@echo "$(GREEN)Done!$(NOCOLOR)"

make_libraries:
	@make -sC $(SRC_DIR)/libft
	@make -sC $(SRC_DIR)/minilibx*

clean:
	@$(RM) $(BUILD_DIR)

fclean: clean
	@$(RM) $(NAME)
	@make fclean -sC $(SRC_DIR)/libft
	@make clean -sC $(SRC_DIR)/minilibx*

re: fclean
	$(MAKE)

run: $(NAME)
	@echo "Initializing $(PURPLE)so_long...$(NOCOLOR)"
	@./$(NAME)
