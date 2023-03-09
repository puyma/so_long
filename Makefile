# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/27 13:10:44 by mpuig-ma          #+#    #+#              #
#    Updated: 2023/03/09 22:57:39 by mpuig-ma         ###   ########.fr        #
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

SRC_FILES	:=	src/main.c
BONUS_FILES	:=	$(SRC_FILES)
# BONUS_FILES	:=	$(addsuffix _bonus.c, $(basename $(SRC_FILES)))

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

debug: $(LIBFT) $(LIBMLX) $(OBJ_FILES) $(DEP_FILES) src/$(NAME).h
	$(CC) $(DEBUG) $(INC) $(CFLAGS) $(LFLAGS) $(SRC_FILES) -o $(NAME)
	@echo "Built $(STYLE)$(NAME)$(NOSTYLE) (debug)"

all: $(NAME)
