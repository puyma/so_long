/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:47:51 by mpuig-ma          #+#    #+#             */
/*   Updated: 2022/10/27 20:01:23 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

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

int	ft_nothing(int x, int y, t_game *game)
{
	(void) game;
	ft_printf("mousemove> : %d, Y: %d\n", x, y);
	return (0);
}

int	ft_mousecode(int button, int x, int y, t_game *game)
{
	ft_printf("button: %d, x: %d, y: %d\n", button, x, y);
	(void) game;
	return (0);
}
