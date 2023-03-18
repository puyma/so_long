# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/27 13:10:44 by mpuig-ma          #+#    #+#              #
#    Updated: 2023/03/18 20:26:48 by mpuig-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

AUTHOR		?=	mpuig-ma

BUILD_DIR	:=	build
SRC_DIR		:=	src
LIBFT_DIR	:=	$(SRC_DIR)/libft
LIBMLX_DIR	:=	$(SRC_DIR)/libmlx

LIBFT		:=	$(LIBFT_DIR)/libft.a
LIBMLX		:=	$(LIBMLX_DIR)/libmlx.a
NAME		:=	so_long

CC			:=	gcc
CFLAGS		:=	-Wall -Werror -Wextra -O3
CFLAGS		+=	-MMD
LFLAGS		:=	-L./$(LIBMLX_DIR) -lmlx -L./$(LIBFT_DIR) -lft
LFLAGS		+=	-lm
LFLAGS		+=	-framework OpenGL -framework Appkit
DEBUG		:=	-g -fsanitize='address,undefined' -Og
#CFLAGS		+=	$(DEBUG)
INC			:=	-I./$(LIBFT_DIR)/src -I./$(LIBMLX_DIR)
RM			:=	rm -rf

OS			:=	$(shell uname)
ifeq ($(OS),Linux)
	LFLAGS	+=	-lXext -lX11
endif

NOSTYLE		:=	\033[0m
STYLE		:=	\033[0;32m
PURPLE		:=	\033[1;35m
TERM_COLORS	:=	$(shell tput colors)

ifeq ($(TERM_COLORS), 256)
	PURPLE	:=	\033[1;38;5;135m
endif

SRC_FILES	:=	src/animation.c src/board.c src/check.c src/display_nmoves.c \
				src/events.c src/exit.c src/game.c src/images.c \
				src/launch.c src/locate.c src/log.c src/main.c src/map.c \
				src/move.c src/path.c src/put_image.c src/window.c

BONUS_FILES	:=	$(addsuffix _bonus.c, $(basename $(SRC_FILES))) \
				src/pause_bonus.c src/write_map_bonus.c

OBJ_FILES	=	$(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(notdir $(basename $(SRC_FILES)))))
DEP_FILES	=	$(addprefix $(BUILD_DIR)/, $(addsuffix .d, $(notdir $(basename $(SRC_FILES)))))
B_OBJ_FILES	=	$(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(notdir $(basename $(BONUS_FILES)))))
B_DEP_FILES	=	$(addprefix $(BUILD_DIR)/, $(addsuffix .d, $(notdir $(basename $(BONUS_FILES)))))

.PHONY: clean fclean re all debug

#mv generator (&functions) to bonus files (&rule/target)

$(NAME): $(LIBFT) $(LIBMLX) $(OBJ_FILES) $(DEP_FILES) src/$(NAME).h
	$(CC) $(INC) $(CFLAGS) $(LFLAGS) -O3 $(SRC_FILES) -o $(basename $@)
	@echo "Built $(STYLE)$(basename $@)$(NOSTYLE)"
	
bonus generator: $(LIBFT) $(LIBMLX) $(B_OBJ_FILES) $(B_DEP_FILES) src/$(NAME).h
	$(CC) $(INC) $(CFLAGS) $(LFLAGS) -lz -O3 $(BONUS_FILES) -D$(shell echo $@ | tr '[:lower:]' '[:upper:]') -o $(basename $@)
	@echo "Built $(STYLE)$(basename $@)$(NOSTYLE)"

$(LIBFT) $(LIBMLX):
	make -C $(dir $@)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c 
	@mkdir -p $(@D)
	$(CC) $(INC) $(CFLAGS) $(CCFLAGS) -c $< -o $@

clean:
	$(RM) $(BUILD_DIR)/ $(LIBFT) $(LIBMLX)
	make fclean -C $(LIBFT_DIR)
	make clean -C $(LIBMLX_DIR)

fclean: clean
	$(RM) $(NAME)* 
	$(RM) generator* bonus* *.ber

re: fclean
	$(MAKE)

all: $(NAME)
