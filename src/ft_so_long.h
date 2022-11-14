/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_so_long.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:20:32 by mpuig-ma          #+#    #+#             */
/*   Updated: 2022/11/08 15:03:01 by mpuig-ma         ###   ########.fr       */
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
# include "libft/src/libft.h"
# include "minilibx/mlx.h"

# define PIX_SIZE		50 // 42 ???? yess
# define DEF_WIDTH		PIX_SIZE * 10
# define DEF_HEIGHT		PIX_SIZE * 10

# define FILENAME_LEN	42

# define EMPTY_SPACE	0
# define WALL			1
# define MAP_EXIT		E
# define COLLECTIBLE	C

typedef struct	s_imgdata
{
	void		*img;
	char		*address;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_imgdata;

typedef struct	s_game
{
	void		*mlx;
	void		*mlx_window;
	void		*img;
	int			mlx_window_width;
	int			mlx_window_height;
	int			size;
	t_list		**buttons;
}				t_game;

void	ft_mlx_pixel_put(t_imgdata *data, int x, int y, int color);

int		ft_launch(const char *input);
int		ft_launch_graphics(void);
int		ft_check_map(const char *input);

int		ft_destroy(t_game *game);
int		ft_keycode(int keycode, t_game *game);
int		ft_nothing(int x, int y, t_game *game);
int		ft_mousecode(int button, int x, int y, t_game *game);

int		ft_draw_rectangle(int x, int y, int width, int height, t_imgdata *img);

int		ft_do_motion_events(int x, int y, t_game *game);

int		ft_test(void);

int		ft_set_events(t_game *game);

#endif /* ft_so_long.h */
