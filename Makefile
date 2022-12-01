# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/27 13:10:44 by mpuig-ma          #+#    #+#              #
#    Updated: 2022/11/15 16:56:14 by mpuig-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	so_long
AUTHOR		?=	mpuig-ma

LIBFT		:=	libft.a
LIBMLX		:=	libmlx.dylib

BIN_DIR		:=	bin
BUILD_DIR	:=	build
SRC_DIR		:=	src
LIBFT_DIR	:=	$(SRC_DIR)/libft
LIBMLX_DIR	:=	$(SRC_DIR)/libmlx

CC			:=	gcc
CFLAGS		:=	-g -Wall -Werror -Wextra -MMD
LFLAGS		:=	-L./$(LIBMLX_DIR) -lmlx -L./$(LIBFT_DIR) -lft -lm
RM			:=	rm -rf

SRC_FILES	:=	src/ft_button.c src/ft_check_map.c \
				src/ft_check_path.c src/ft_draw_rectangle.c \
				src/ft_events.c src/ft_exit_error.c \
				src/ft_launch.c src/ft_launch_graphics.c \
				src/ft_load_game.c src/ft_log.c \
				src/ft_mlx_pixel_put.c src/ft_so_long.c

NOCOLOR		:=	\033[0m
GREEN		:=	\033[0;32m
PURPLE		:=	\033[1;35m
TERM_COLORS	:=	$(shell tput colors)

# Color codes (improved) for 256 terminals

ifeq ($(TERM_COLORS), 256)
	PURPLE	:=	\033[1;38;5;135m
endif

# .o to .c rule

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@
	$(call msg,Compiled,$(notdir $<))

OBJS	=	$(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(notdir $(basename $(SRC_FILES)))))
DEPS	=	$(addprefix $(BUILD_DIR)/, $(addsuffix .d, $(notdir $(basename $(SRC_FILES)))))

.PHONY: all make_libraries fclean clean re

all: $(NAME)

$(NAME): $(LIBFT) $(LIBMLX) $(SRC_FILES)
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CFLAGS) $(LFLAGS) $(SRC_FILES) -o $(BIN_DIR)/$(NAME)

$(LIBFT):
	make -C $(SRC_DIR)/libft
	cp -f $(SRC_DIR)/libft/$(LIBFT) ./
	
$(LIBMLX):
	make -C $(SRC_DIR)/libmlx
	mkdir -p $(BIN_DIR)
	cp -f $(SRC_DIR)/libmlx/$(LIBMLX) ./

clean:
	$(RM) $(BUILD_DIR)
	$(RM) $(LIBFT)
	$(RM) $(LIBMLX)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(BIN_DIR)
	@make fclean -C $(SRC_DIR)/libft
	@make clean -C $(SRC_DIR)/libmlx

re: fclean
	$(MAKE)