
NAME		:=	libmlx.dylib
VERSION		:=	v20210621

MODULE_SRC	:=	mlx_image.swift mlx_window.swift mlx_init.swift
MODULE_OBJ	=	$(MODULE_SRC:.swift=.swiftmodule)

SRC			:=	interface.swift $(MODULE_SRC)
OBJ			=	$(SRC:.swift=.o)

C_SRC		:=	mlx_xpm.c mlx_png.c mlx_string_put.c
C_OBJ		=	$(C_SRC:.c=.o)
CFLAGS		:=	-O3

INC			:=	-I.
#OPTI		:=	-Ounchecked

NOCOLOR		:=	\033[0m
GREEN		:=	\033[0;32m
PURPLE		:=	\033[1;35m
TERM_COLORS	:=	$(shell tput colors)

# Color codes (improved) for 256 terminals

ifeq ($(TERM_COLORS), 256)
	PURPLE	:=	\033[1;38;5;135m
endif

%.o: %.swift
	swiftc $(OPTI) $(INC) -parse-as-library -c $< -o $@

%.swiftmodule: %.swift
	swiftc $(OPTI) $(INC) -parse-as-library -c $< -o $@ -emit-module -module-name $(patsubst %.swift,%,$<) -module-link-name $(patsubst %.swift,%,$<)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

.PHONY: libmlx all clean

libmlx: $(NAME)
all: $(NAME)

$(NAME): $(MODULE_OBJ) $(OBJ) $(C_OBJ)
	swiftc $(OPTI) $(INC) -o $(NAME) -emit-library $(OBJ) $(C_OBJ) -lz

clean:
	rm -rf $(NAME)
	rm -rf $(OBJ)
	rm -rf $(MODULE_OBJ)
	rm -rf $(C_OBJ)
	rm -rf *.swiftdoc *~ *.swiftsourceinfo
