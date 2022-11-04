/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_so_long.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:20:32 by mpuig-ma          #+#    #+#             */
/*   Updated: 2022/11/04 22:45:45 by mpuig-ma         ###   ########.fr       */
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
# include "../src/libft/src/libft.h"
# include "../src/minilibx-macos/mlx.h"

# define DEF_WIDTH	640
# define DEF_HEIGHT	640

typedef struct	s_data
{
	void		*img;
	char		*address;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct	s_game
{
	void		*mlx;
	void		*mlx_window;
	int			mlx_window_width;
	int			mlx_window_height;
	void		*img;
	t_list		**buttons;
}				t_game;

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color);

int		ft_launch(const char *input);
int		ft_launch_graphics(void);
int		ft_check_map(const char *input);

int		ft_destroy(t_game *game);
int		ft_keycode(int keycode, t_game *game);
int		ft_nothing(int x, int y, t_game *game);
int		ft_mousecode(int button, int x, int y, t_game *game);

int		ft_draw_rectangle(int x, int y, int width, int height, t_data *img);

int		ft_test(void);

#endif /* ft_so_long.h */
