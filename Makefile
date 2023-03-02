# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/27 13:10:44 by mpuig-ma          #+#    #+#              #
#    Updated: 2023/03/02 14:47:13 by mpuig-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

AUTHOR		?=	mpuig-ma

BUILD_DIR	:=	build
SRC_DIR		:=	src
LIBFT_DIR	:=	$(SRC_DIR)/libft
LIBMLX_DIR	:=	$(SRC_DIR)/libmlx

LIBFT		:=	libft.a
LIBMLX		:=	libmlx.a
NAME		:=	so_long

CC			:=	gcc
CFLAGS		:=	-Wall -Werror -Wextra -O3
CCFLAGS		:=	-MMD
LFLAGS		:=	-L./$(LIBMLX_DIR) -lmlx -L./$(LIBFT_DIR) -lft
LFLAGS		+=	-lm
LFLAGS		+=	-framework OpenGL -framework Appkit
DEBUG		:=	-g -fsanitize='address,undefined' -Og
INC			:=	-I./$(LIBFT_DIR)/src -I./$(LIBMLX_DIR)
RM			:=	rm -rf

NOSTYLE		:=	\033[0m
STYLE		:=	\033[0;32m
PURPLE		:=	\033[1;35m
TERM_COLORS	:=	$(shell tput colors)

ifeq ($(TERM_COLORS), 256)
	PURPLE	:=	\033[1;38;5;135m
endif

SRC_FILES	:=	src/events.c src/launch.c src/load_images.c src/log.c src/main.c src/map.c \
				src/map_check.c src/move.c src/movement.c src/path.c \
				src/put_images.c src/utils.c src/window.c
				
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
	$(RM) $(NAME)* generator

re: fclean
	$(MAKE)

debug: $(LIBFT) $(LIBMLX) $(OBJ_FILES) $(DEP_FILES) src/$(NAME).h
	$(CC) $(DEBUG) $(INC) $(CFLAGS) $(LFLAGS) $(SRC_FILES) -o $(NAME)
	@echo "Built $(STYLE)$(NAME)$(NOSTYLE) (debug)"

all: $(NAME)
