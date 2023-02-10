# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/27 13:10:44 by mpuig-ma          #+#    #+#              #
#    Updated: 2023/02/10 12:42:30 by mpuig-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

AUTHOR		?=	mpuig-ma

BUILD_DIR	:=	build
SRC_DIR		:=	src
LIBFT_DIR	:=	$(SRC_DIR)/libft
LIBMLX_DIR	:=	$(SRC_DIR)/libmlx

LIBFT		:=	libft.a
LIBMLX		:=	libmlx.dylib
NAME		:=	so_long

CC			:=	gcc
CFLAGS		:=	-Wall -Werror -Wextra
CCFLAGS		:=	-MMD
LFLAGS		:=	-L./$(LIBMLX_DIR) -lmlx -L./$(LIBFT_DIR) -lft -lm
INC			:=	-I./$(LIBFT_DIR)/src -I./$(LIBMLX_DIR)
RM			:=	rm -rf

NOSTYLE		:=	\033[0m
STYLE		:=	\033[0;32m
PURPLE		:=	\033[1;35m
TERM_COLORS	:=	$(shell tput colors)

ifeq ($(TERM_COLORS), 256)
	PURPLE	:=	\033[1;38;5;135m
endif

SRC_FILES	:=	src/ft_button.c \
				src/ft_draw_rectangle.c \
				src/ft_events.c \
				src/ft_exit_error.c \
				src/ft_launch.c \
				src/ft_launch_graphics.c \
				src/ft_load_game.c \
				src/ft_map.c \
				src/ft_map_content.c \
				src/ft_map_path.c \
				src/ft_mlx_pixel_put.c \
				src/ft_utils.c \
				src/main.c

OBJ_FILES	=	$(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(notdir $(basename $(SRC_FILES)))))
DEP_FILES	=	$(addprefix $(BUILD_DIR)/, $(addsuffix .d, $(notdir $(basename $(SRC_FILES)))))

.PHONY: clean fclean re all

$(NAME): $(LIBFT) $(LIBMLX) $(OBJ_FILES) #$(DEP_FILES)
	$(CC) $(INC) $(CFLAGS) $(LFLAGS) $(SRC_FILES) -o $(NAME)
	@echo "Built $(STYLE)$(NAME)$(NOSTYLE)"
	
$(LIBFT) $(LIBMLX):
	make -C $(SRC_DIR)/$(basename $@)
	cp -f $(SRC_DIR)/$(basename $@)/$@ ./
	
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c 
	@mkdir -p $(@D)
	$(CC) $(INC) $(CFLAGS) $(CCFLAGS) -c $< -o $@

clean:
	$(RM) $(BUILD_DIR)/ $(LIBFT) $(LIBMLX)
	make fclean -C $(SRC_DIR)/libft
	make clean -C $(SRC_DIR)/libmlx

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE)

all: $(NAME)
