/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:10:16 by mpuig-ma          #+#    #+#             */
/*   Updated: 2022/10/12 21:34:16 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "ft_so_long.h"

#define WIDTH 420
#define HEIGHT 420

typedef struct	s_data
{
	void	*img;
	char	*address;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct	s_game
{
	void	*mlx;
	void	*mlx_window;
	void	*img;
}			t_game;

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	int offset = (y * data->line_length + x * (data->bits_per_pixel / 8));
	dst = data->address + offset;
	*(unsigned int*)dst = color;
}

int	ft_close(int keycode, t_game *game)
{
	(void) game;
	ft_putnbr(keycode);
	if (keycode == 53)
		mlx_destroy_window(game->mlx, game->mlx_window);
	exit (0);
}

int	ft_launch_game(void)
{
	t_game	game;
	t_data	img;

	game.mlx = mlx_init();
	game.mlx_window = mlx_new_window(game.mlx, WIDTH, HEIGHT, "TDB");

	img.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	img.address = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	int x = 0;
	int y = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			ft_mlx_pixel_put(&img, x, y, 0x00FF0000);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(game.mlx, game.mlx_window, img.img, 0, 0);
	x = WIDTH / 4;
	y = HEIGHT / 4;
	while (x < WIDTH)
	{
		y = HEIGHT / 4;
		while (y < HEIGHT)
		{
			ft_mlx_pixel_put(&img, x, y, 0x000000CC);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(game.mlx, game.mlx_window, img.img, 0, 0);
	mlx_key_hook(game.mlx_window, &ft_close, &game);
	mlx_loop(game.mlx);
	return (0);
}

int	ft_launch(const char *input)
{
	int	fd;

	fd = open(input, O_RDONLY);
	if (fd == -1)
	{
		strerror(2);
		return (2);
	}
	ft_check_map(fd);
	ft_launch_game();
	write(1, "We are all in this together!\n", 30);
	return (0);
}
