# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/08 10:09:52 by mpuig-ma          #+#    #+#              #
#    Updated: 2022/10/08 11:45:21 by mpuig-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# MODIFIED Makefile by $(AUTHOR)

NAME	:= libmlx.dylib

MODULE_SRC= mlx_image.swift mlx_window.swift mlx_init.swift
MODULE_OBJ=$(MODULE_SRC:.swift=.swiftmodule)

SRC= interface.swift $(MODULE_SRC)
OBJ=$(SRC:.swift=.o)

C_SRC= mlx_xpm.c mlx_png.c mlx_string_put.c
C_OBJ=$(C_SRC:.c=.o)
CFLAGS=-O3

INC=-I.
#OPTI=-Ounchecked

NOCOLOR		:= \033[0m
GREEN		:= \033[0;32m
PURPLE		:= \033[1;35m
TERM_COLORS	:= $(shell tput colors)

# Color codes (improved) for 256 terminals

ifeq ($(TERM_COLORS), 256)
	PURPLE	:= \033[1;38;5;135m
endif

%.o: %.swift
	@swiftc $(OPTI) $(INC) -parse-as-library -c $< -o $@
	@echo "$(GREEN)Compiled $(NOCOLOR)$<"

%.swiftmodule: %.swift
	@swiftc $(OPTI) $(INC) -parse-as-library -c $< -o $@ -emit-module -module-name $(patsubst %.swift,%,$<) -module-link-name $(patsubst %.swift,%,$<)
	@echo "$(GREEN)Compiled $(NOCOLOR)(?)$<"

%.o: %.c
	@gcc -O3 -c $< -o $@
	@echo "$(GREEN)Compiled $(NOCOLOR)$<"

.PHONY: clean

all: $(NAME)

$(NAME): $(MODULE_OBJ) $(OBJ) $(C_OBJ)
	@swiftc $(OPTI) $(INC) -o $(NAME) -emit-library $(OBJ) $(C_OBJ) -lz
	@echo "$(GREEN)Linked $(NOCOLOR)$(NAME) \033[3mv20210621 for macOS"

clean:
	@rm -rf $(NAME) $(OBJ) $(MODULE_OBJ) $(C_OBJ) *.swiftdoc *~
