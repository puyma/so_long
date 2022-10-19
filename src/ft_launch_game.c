/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_game.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:10:16 by mpuig-ma          #+#    #+#             */
/*   Updated: 2022/10/19 19:35:15 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	int offset = (y * data->line_length + x * (data->bits_per_pixel / 8));
	dst = data->address + offset;
	*(unsigned int*)dst = color;
}

int	ft_destroy(t_game *game)
{
	mlx_destroy_window(game->mlx, game->mlx_window);
	exit(0);
	return (0);
}
int	ft_keycode(int keycode, t_game *game)
{
	(void) game;
	write(1, "Pressed key: ", 13);
	ft_putnbr(keycode);
	write(1, "\n", 1);
	if (keycode == KEY_ESC)
		mlx_clear_window(game->mlx, game->mlx_window);
	return (0);
}

int	ft_nothing(t_game *game)
{
	(void) game;
	//write(1, "Nothing is happening...\n", 24);
	return (0);
}

int	ft_mousecode(int button, int x, int y, t_game *game)
{
	ft_printf("button: %d, x: %d, y: %d\n", button, x, y);
	(void) game;
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
	//ft_check_map(fd);
	ft_launch_graphics();
	write(1, "We are all in this together!\n", 30);
	return (0);
}
