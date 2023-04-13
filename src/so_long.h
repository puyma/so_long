/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:20:32 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/03/15 11:35:16 by mpuig-ma         ###   ########.fr       */
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

# define PIX_SIZE		32
# define FILENAME_LEN	42
# ifdef GENERATOR
#  ifndef LOG_LEVEL
#   define LOG_LEVEL	1
#  endif
# else
#  ifndef LOG_LEVEL
#   define LOG_LEVEL	0
#  endif
# endif

# define C_EMPTY_SPACE	'0'
# define C_WALL			'1'
# define C_COLLECTIBLE	'C'
# define C_EXIT			'E'
# define C_PLAYER		'P'
# define C_ENEMY		'N'

# ifdef BONUS
#  define C_ALLOWED		"01CEPN"
# elif GENERATOR
#  define C_ALLOWED		"01CEPN"
# else
#  define C_ALLOWED		"01CEP"
# endif

# define MAP_EXT		".ber"

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
# define KEY_N			45

# define FLOOR			"./src/assets/floor.xpm"
# define WALL			"./src/assets/wall.xpm"
# define COLLECTIBLE	"./src/assets/collectible.xpm"
# define EXIT			"./src/assets/exit.xpm"
# define PLAYER			"./src/assets/player.xpm"
# define BLUR			"./src/assets/blur.png"
# define PAUSE			"./src/assets/pause.png"
# define ENEMY			"./src/assets/enemy.png"

enum e_game { Stopped = 0, Running, Paused, Stopping, Ended, Won, Lost } state;
enum e_event { ON_KEYDOWN = 2, ON_KEYUP = 3, ON_DESTROY = 17 }	event;
enum e_character { None = 0, Left, Right, Up, Down }			direction;

typedef struct s_imgdata
{
	void		*img;
	char		*address;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_imgdata;

typedef struct s_vector
{
	int			x;
	int			y;
}				t_vector;

typedef struct s_map
{
	char		*filename;
	size_t		width;
	size_t		height;
	t_list		*list;
	int			**board;
}				t_map;

typedef struct s_game
{
	void		*mlx;
	void		*mlx_window;
	enum e_game	state;
	size_t		size;
	size_t		width;
	size_t		height;
	int			**board;
	t_imgdata	*i_floor;
	t_imgdata	*i_wall;
	t_imgdata	*i_collectible;
	t_imgdata	*i_exit;
	t_imgdata	*i_player;
	t_imgdata	*i_blur;
	t_imgdata	*i_pause;
	t_imgdata	*i_enemy;
	t_list		*collectibles;
	t_vector	*exit;
	t_vector	*player;
	size_t		n_moves;
	size_t		n_collectible;
	size_t		n_exit;
	size_t		n_player;
	char		*filename;
	t_map		*map;
}				t_game;

int				ft_additional_check(t_game *game);
int				ft_check_map(t_map *map);
int				ft_check_path(t_game *game);
int				ft_destroy(t_game *game);
int				ft_display_nmoves(t_game *game, int background);
int				ft_extension_isvalid(char *filename, char *ext);
void			ft_exit(char *str, int num, void (*f)(void *), void *ptr);
int				ft_fill_window(t_game *game, t_imgdata *img);
int				ft_generate_map(char *filename, int x, int y);
t_vector		*ft_ismovekey(int keycode);
int				ft_keycode(int keycode, t_game *game);
int				ft_launch(t_game *game);
int				ft_load_board(t_map *map);
int				ft_load_game(t_game *game);
t_vector		*ft_locate_character(int **board, int x, int y, int c);
t_list			*ft_locate_items(int **board, int c);
int				ft_load_map(t_map *map);
void			ft_log(char *str);
void			ft_log_state(enum e_game state);
int				ft_memload_images(t_game *game);
t_imgdata		*ft_memload_img(t_game *game, char *filename);
void			ft_memunload_images(t_game *game);
int				ft_move(t_game *game, t_vector *player, t_vector *direction);
int				**ft_new_board(size_t x, size_t y);
t_game			*ft_new_game(t_map *map);
t_map			*ft_new_map(char *filename);
void			*ft_new_window(t_game *game, char *title);
int				ft_put_default_img(t_game *game, int x, int y);
int				ft_put_images(t_game *game);
int				ft_put_img(t_game *game, t_imgdata *img, int x, int y);
int				ft_put_img_xy(t_game *game, t_imgdata *img, int x, int y);
int				ft_slide(t_game *game, t_vector *player, t_vector *direction);
void			ft_sleep(long long sleep_time);
int				ft_state_render(t_game *game);
int				ft_toggle_pause(t_game *game);
int				ft_unload_board(int **board);
void			ft_write_map(char *filename, int **board);

void			ft_animate_player(t_game *game, t_vector *player, t_vector *d);

#endif /* so_long.h */
