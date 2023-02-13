/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_so_long.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:20:32 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/13 10:58:49 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SO_LONG_H
# define FT_SO_LONG_H

# include <unistd.h> /* write, close, read */
# include <fcntl.h> /* open */
# include <stdlib.h> /* malloc, free, exit */
# include <stdio.h> /* perror */
# include <string.h> /* strerror */

# include "ft_button.h"
# include "ft_keycodes.h"
# include "libft.h"
# include "mlx.h"

# define LOG_LEVEL		1
# define PIX_SIZE		42
# define FILENAME_LEN	42

# define EMPTY_SPACE	'0'
# define WALL			'1'
# define MAP_EXIT		'E'
# define COLLECTIBLE	'C'
# define PLAYER			'P'

# define ALLOWED_CHARS	"01CEP"

# define FLOOR			"./src/assets/green.xpm"

# define ERR_00 "Something went wrong..."
# define ERR_01 "Filename is not valid"
# define ERR_02 ""
# define ERR_03 ""
# define ERR_04 ""
# define ERR_05 ""
# define ERR_06 ""
# define ERR_07 ""
# define ERR_08 ""
# define ERR_09 ""
# define ERR_0A ""
# define ERR_0B ""
# define ERR_0C ""
# define ERR_0D ""
# define ERR_0E ""
# define ERR_0F ""
# define ERR_RECT "Map is not rectangular"
# define ERR_CHAR "Found some shit inside your fmap"

typedef struct s_map {
	char		*filename;
	int			fd;
	t_list		*lst;
	unsigned	lstsize;
	size_t		lnlen;
	char		c_empty_space;
	char		c_wall;
	char		c_map_exit;
	char		c_collectible;
	int			exit_err;
	char		*exit_str;
}				t_map;

typedef struct s_imgdata {
	void		*img;
	char		*address;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_imgdata;

typedef struct s_game {
	void		*mlx;
	void		*mlx_window;
	void		*img;
	int			height;
	int			width;
	int			mlx_window_width;
	int			mlx_window_height;
	int			size;
	t_list		**buttons;
}				t_game;

void	ft_mlx_pixel_put(t_imgdata *data, int x, int y, int color);

int		ft_launch(const char *input_file);
int		ft_launch_graphics(void);
int		ft_map_isvalid(t_map *map);

int		ft_destroy(t_game *game);
int		ft_keycode(int keycode, t_game *game);
int		ft_nothing(int x, int y, t_game *game);
int		ft_mousecode(int button, int x, int y, t_game *game);

int		ft_do_motion_events(int x, int y, t_game *game);
int		ft_test(void);
int		ft_set_events(t_game *game);

void	ft_exit_error(int error_num);
void	ft_exit_str(char *error_str, int error_num);

void	ft_delete_nl(void *);
int		ft_check_characters(t_map *map);
int		ft_check_surroundings(t_map *map);
int		ft_path_isvalid(t_map *map);

#endif /* ft_so_long.h */
