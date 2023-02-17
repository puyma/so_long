# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/27 13:10:44 by mpuig-ma          #+#    #+#              #
#    Updated: 2023/02/17 18:29:25 by mpuig-ma         ###   ########.fr        #
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
CFLAGS		:=	-Wall -Werror -Wextra
CCFLAGS		:=	-MMD
LFLAGS		:=	-L./$(LIBMLX_DIR) -lmlx -L./$(LIBFT_DIR) -lft -lm -lz -framework OpenGL -framework Appkit
DEBUG		:=	-g
INC			:=	-I./$(LIBFT_DIR)/src -I./$(LIBMLX_DIR)
RM			:=	rm -rf

NOSTYLE		:=	\033[0m
STYLE		:=	\033[0;32m
PURPLE		:=	\033[1;35m
TERM_COLORS	:=	$(shell tput colors)

ifeq ($(TERM_COLORS), 256)
	PURPLE	:=	\033[1;38;5;135m
endif

SRC_FILES	:=	src/events.c \
				src/launch.c \
				src/images.c \
				src/map.c \
				src/utilities.c \
				src/main.c

OBJ_FILES	=	$(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(notdir $(basename $(SRC_FILES)))))
DEP_FILES	=	$(addprefix $(BUILD_DIR)/, $(addsuffix .d, $(notdir $(basename $(SRC_FILES)))))

.PHONY: clean fclean re all debug

$(NAME): $(LIBFT) $(LIBMLX) $(OBJ_FILES) $(DEP_FILES) src/$(NAME).h
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

debug: $(LIBFT) $(LIBMLX) $(OBJ_FILES) $(DEP_FILES) src/$(NAME).h
	$(CC) $(DEBUG) $(INC) $(CFLAGS) $(LFLAGS) $(SRC_FILES) -o $(NAME)
	@echo "Built $(STYLE)$(NAME)$(NOSTYLE) (debug)"

all: $(NAME)
