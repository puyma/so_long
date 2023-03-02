NAME	:=	libmlx.a
SRC		:=	mlx_shaders.c mlx_new_window.m \
			mlx_init_loop.m mlx_new_image.m \
			mlx_xpm.c mlx_int_str_to_wordtab.c
SRC		+=	mlx_png.c mlx_mouse.m
OBJ1	=	$(SRC:.c=.o)
OBJ		=	$(OBJ1:.m=.o)
CFLAGS	+=	-O2 -Wno-deprecated

# add to match string put with X11 in size and position
CFLAGS	+=	-DSTRINGPUTX11

NOCOLOR	:= \033[0m
GREEN	:= \033[0;32m

.PHONY: clean re

$(NAME): $(OBJ)
	ar -r $(NAME) $(OBJ)
	ranlib $(NAME)
	@echo "Linked $(GREEN)$(NAME)$(NOCOLOR)"
	
clean:
	rm -f $(NAME) $(OBJ) *~
	rm -f mlx_app

re: clean all

all: $(NAME)
