# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/27 13:10:44 by mpuig-ma          #+#    #+#              #
#    Updated: 2022/11/08 16:31:11 by mpuig-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= so_long
AUTHOR		?= mpuig-ma

CC			:= gcc
CFLAGS		:= -g -Wall -Werror -Wextra #-MMD
LFLAGS		:= -L./src/libft -lft -L./src/minilibx-macos -lmlx -lm 
FRAMEWORK	:= -framework OpenGL -framework AppKit
RM			:= rm -rf
SRC_DIR		:= src
BUILD_DIR	:= build
BIN_DIR		:= bin

LIBFT		:= libft.a
LIBMLX		:= libmlx.dylib

SRC_FILES	:= src/ft_check_map.c \
			   src/ft_button.c \
			   src/ft_draw_rectangle.c \
			   src/ft_events.c \
			   src/ft_launch.c \
			   src/ft_launch_graphics.c \
			   src/ft_load_game.c \
			   src/ft_mlx_pixel_put.c \
			   src/ft_so_long.c

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
	@mkdir -p $(BIN_DIR)
	@$(CC) $(FLAGS) $(SRC_FILES) $(LFLAGS) $(FRAMEWORK) -o $(BIN_DIR)/$(NAME)

$(NAME)::
ifeq (,$(findstring s,$(MAKEFLAGS)))
	@echo "$(GREEN)Done!$(NOCOLOR)"
endif

make_libraries:
	@make -sC $(SRC_DIR)/libft
	@make -sC $(SRC_DIR)/minilibx-macos
	@cp $(SRC_DIR)/minilibx-macos/$(LIBMLX) $(BIN_DIR)/

clean:
	@$(RM) $(BUILD_DIR) $(LIBMLX)

fclean: clean
	@$(RM) $(BIN_DIR) $(NAME)
	@make fclean -sC $(SRC_DIR)/libft
	@make clean -sC $(SRC_DIR)/minilibx-macos

re: fclean
	$(MAKE)

run: $(NAME)
	@echo "Initializing $(PURPLE)so_long...$(NOCOLOR)"
	@./$(BIN_DIR)/$(NAME)
