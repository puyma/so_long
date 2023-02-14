/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_so_long.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:20:32 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/14 13:49:59 by mpuig-ma         ###   ########.fr       */
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
# define PIX_SIZE		26
# define FILENAME_LEN	42

# define C_EMPTY_SPACE	'0'
# define C_WALL			'1'
# define C_COLLECTIBLE	'C'
# define C_EXIT			'E'
# define C_PLAYER		'P'

# define C_ALLOWED		"01CEP"

# define FLOOR			"./src/assets/floor.xpm"
# define WALL			"./src/assets/wall.xpm"
# define COLLECTIBLE	"./src/assets/collectible.xpm"
# define EXIT			"./src/assets/exit.xpm"
# define PLAYER			"./src/assets/player.xpm"

# define ERR_00			"Something went wrong..."
# define ERR_01			"Filename is not valid"
# define ERR_02			""
# define ERR_03			""
# define ERR_04			""
# define ERR_05			""
# define ERR_06			""
# define ERR_07			""
# define ERR_08			""
# define ERR_09			""
# define ERR_0A			""
# define ERR_0B			""
# define ERR_0C			""
# define ERR_0D			""
# define ERR_0E			""
# define ERR_0F			""
# define ERR_RECT		"Map is not rectangular"
# define ERR_CHAR		"Found some shit inside your fmap"

typedef struct s_imgdata
{
	void			*img;
	char			*address;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
}					t_imgdata;

typedef struct s_map_item
{
	char			c;
	t_imgdata		img;
}					t_map_item;

typedef struct s_map
{
	char			*filename;
	int				fd;
	t_list			*lst;
	unsigned int	lstsize;
	size_t			lnlen;
	int				exit_err;
	char			*exit_str;
	t_map_item		**arr;
	char			c_floor;
	char			c_wall;
	char			c_collectible;
	char			c_exit;
	char			c_player;
}					t_map;

typedef struct s_game
{
	void			*mlx;
	void			*mlx_window;
	void			*img;
	int				height;
	int				width;
	t_map			*map;
	int				mlx_window_width;
	int				mlx_window_height;
	int				size;
	t_list			**buttons;
	t_imgdata		*floor;
	t_imgdata		*wall;
	t_imgdata		*collectible;
	t_imgdata		*exit;
	t_imgdata		*player;
}					t_game;

void	ft_mlx_pixel_put(t_imgdata *data, int x, int y, int color);

int		ft_launch(const char *input_file);
int		ft_launch_graphics(t_map *map);
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

void	ft_delete_nl(void *ptr);
int		ft_check_characters(t_map *map);
int		ft_check_surroundings(t_map *map);
int		ft_path_isvalid(t_map *map);

#endif /* ft_so_long.h */
