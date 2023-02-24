/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:20:32 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/24 09:45:50 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h> /* write, close, read */
# include <fcntl.h> /* open */
# include <stdlib.h> /* malloc, free, exit */
# include <stdio.h> /* perror */
# include <string.h> /* strerror */

# include "libft.h"
# include "mlx.h"

# define LOG_LEVEL		0
# define PIX_SIZE		32
# define FILENAME_LEN	42

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

# define FLOOR			"./src/assets/floor.png"
# define WALL			"./src/assets/wall.png"
# define COLLECTIBLE	"./src/assets/collectible.png"
# define EXIT			"./src/assets/exit.png"
# define PLAYER			"./src/assets/player.png"
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
# define ERR_PATH		"Path is invalid"
# define ERR_IMG_LOAD	"Could not load image"

typedef struct s_imgdata
{
	void				*img;
	char				*address;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	int					width;
	int					height;
}						t_imgdata;

typedef struct s_map_item
{
	char				c;
	t_imgdata			img;
}						t_map_item;

typedef struct s_map
{
	char				*filename;
	int					fd;
	t_list				*lst;
	unsigned int		lstsize;
	size_t				lnlen;
	int					exit_err;
	char				*exit_str;
	t_map_item			**arr;
	int					n_collectible;
	int					n_exit;
	int					n_player;
}						t_map;

enum e_game { Stopped = 0, Running, Paused, Stopping }	state;

enum e_character { None = 0, Left, Right, Up, Down }	direction;

enum e_event { ON_KEYDOWN = 2, ON_KEYUP = 3, ON_DESTROY = 17 }	event;

typedef struct s_vector
{
	int					x;
	int					y;
}						t_vector;

typedef struct s_character
{
	int					x;
	int					y;
}						t_character;

typedef struct s_game
{
	void				*mlx;
	void				*mlx_window;
	int					mlx_window_width;
	int					mlx_window_height;
	int					height;
	int					width;
	t_map				*map;
	int					size;
	t_list				**buttons;
	t_imgdata			*i_floor;
	t_imgdata			*i_wall;
	t_imgdata			*i_collectible;
	t_imgdata			*i_exit;
	t_imgdata			*i_player;
	t_imgdata			*i_blur;
	t_imgdata			*i_pause;
	unsigned int		n_moves;
	enum e_game			state;
	t_character			player;
	t_character			end_gate;
	int					k_up;
	int					k_down;
	int					k_left;
	int					k_right;
}						t_game;

int			ft_launch(const char *input_file);
int			ft_launch_graphics(t_map *map);
int			ft_map_isvalid(t_map *map);

int			ft_destroy(t_game *game);
int			ft_keycode(int keycode, t_game *game);

int			ft_do_motion_events(int x, int y, t_game *game);
int			ft_test(void);
int			ft_set_events(t_game *game);

void		ft_exit_error(int error_num);
void		ft_exit_str(char *error_str, int error_num);

void		ft_delete_nl(void *ptr);

int			ft_filext_isvalid(char *filename, char *ext);

int			ft_memload_images(t_game *game);
t_imgdata	*ft_memload_img(t_game *game, char *filename);
int			ft_put_images(t_game *game);
int			ft_put_img(t_game *game, t_imgdata *img, int x, int y);
int			ft_put_img_xy(t_game *game, t_imgdata *img, int x, int y);
int			ft_put_default_img(t_game *game, int x, int y);
int			ft_fill_window(t_game *game, t_imgdata *img);

int			ft_ismovekey(int keycode);

void		ft_log(char *str);
void		ft_log_state(enum e_game state);

int			ft_toggle_pause(t_game *game);
int			ft_state_render(t_game *game);
int			ft_move(t_game *game, t_character *player, int keycode);

void		*ft_new_window(t_game *game, char *title);
int			ft_filext_isvalid(char *filename, char *ext);

int			ft_check_length(t_map *map);
int			ft_isrectangle(t_map *map);
int			ft_check_characters(t_map *map);
int			ft_check_surroundings(t_map *map);
int			ft_path_isvalid(t_map *map);

#endif /* so_long.h */
