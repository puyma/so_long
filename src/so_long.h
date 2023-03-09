/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:20:32 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/03/09 21:45:30 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h> /* write, close, read */
# include <fcntl.h> /* open */
# include <stdlib.h> /* malloc, free, exit */
# include <stdio.h> /* perror */
# include <string.h> /* strerror */

//# include "libft.h"
//# include "mlx.h"
# include "./libft/src/libft.h"
# include "./libmlx/mlx.h"

# define LOG_LEVEL		0
# define PIX_SIZE		32
# define FILENAME_LEN	42

# ifndef LOG_LEVEL
#  ifdef GENERATOR
#   define LOG_LEVEL	1
#  else /* ifndef GENERATOR */
#   define LOG_LEVEL	0
#  endif
# endif

# define C_EMPTY_SPACE	'0'
# define C_WALL			'1'
# define C_COLLECTIBLE	'C'
# define C_EXIT			'E'
# define C_PLAYER		'P'
# define C_ALLOWED		"01CEP"

# define KEY_A			0
# define KEY_S			1
# define KEY_D			2
# define KEY_W			13
# define KEY_LEFT		123
# define KEY_DOWN		125
# define KEY_RIGHT		124
# define KEY_UP			126
# define KEY_ESC		53
# define KEY_PAUSE		35
# define KEY_0			29
# define KEY_1			18
# define KEY_C			8
# define KEY_E			14
# define KEY_P			35

# define FLOOR			"./src/assets/floor.xpm"
# define WALL			"./src/assets/wall.xpm"
# define COLLECTIBLE	"./src/assets/collectible.xpm"
# define EXIT			"./src/assets/exit.xpm"
# define PLAYER			"./src/assets/player.xpm"
# define BLUR			"./src/assets/blur.png"
# define PAUSE			"./src/assets/pause.png"

# define MAP_EXT		".ber"

# define ERR_00			"Something went wrong..."
# define ERR_01			"Filename is not valid"
# define ERR_02			"Map is empty"
# define ERR_FD			"Could not open fd"
# define ERR_FD_RD		"Could not read from file descriptor"
# define ERR_N_LINES	"All lines should contain the same number of chars"
# define ERR_RECT		"Map is not rectangular"
# define ERR_SURR		"Map is not surrounded by walls"
# define ERR_CHAR		"Found some shit inside your fmap"
# define ERR_CHAR_INV	"Invalid character found in map"
# define ERR_CHAR_TM	"Not a valid amount of player/exit/collectibles"
# define ERR_PATH		"There is not a valid path in this map"
# define ERR_IMG_LOAD	"Could not load image"
# define ERR_IMGS		"Could not load some of the images"

#endif /* so_long.h */
