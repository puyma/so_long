/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:47:51 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/17 14:57:00 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_ismovekey(int keycode);
int	ft_isutilkey(int keycode);

int	ft_move(t_game *game);
int	ft_pause(t_game *game);

int	ft_set_events(t_game *game)
{
	mlx_key_hook(game->mlx_window, &ft_keycode, game);
	mlx_mouse_hook(game->mlx_window, &ft_mousecode, game);
	mlx_hook(game->mlx_window, 17, 0, &ft_destroy, game);
	return (0);
}

int	ft_mousecode(int button, int x, int y, t_game *game)
{
	ft_printf("button: %d, x: %d, y: %d\n", button, x, y);
	(void) game;
	return (0);
}

int	ft_keycode(int keycode, t_game *game)
{
	if (ft_ismovekey(keycode) >= 0)
		ft_move(game);
	else if (keycode == KEY_PAUSE)
		ft_pause(game);
	else if (keycode == KEY_ESC)
	{
		mlx_clear_window(game->mlx, game->mlx_window);
		ft_destroy(game);
	}
	//ft_printf("i> keycode: %d\n", keycode);
	return (0);
}

int	ft_move(t_game *game)
{
	(void) game;
	ft_printf("> Move\n");
	return (0);
}

int	ft_ismovekey(int keycode)
{
	if (keycode == KEY_UP || keycode == KEY_DOWN)
		return (keycode);
	else if (keycode == KEY_W || keycode == KEY_S)
		return (keycode);
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		return (keycode);
	else if (keycode == KEY_A || keycode == KEY_D)
		return (keycode);
	return (-1);
}

int	ft_isutilkey(int keycode)
{
	if (keycode == KEY_ESC || keycode == KEY_PAUSE)
		return (keycode);
	return (0);
}

int	ft_pause(t_game *game)
{
	(void) game;
	ft_printf("> Pause\n");
	return (0);
}

int	ft_destroy(t_game *game)
{
	ft_printf("> Exit\n");
	mlx_destroy_window(game->mlx, game->mlx_window);
	exit(0);
	return (0);
}

//mlx_loop_hook(game->mlx, &ft_nothing, game);
//mlx_hook(game->mlx_window, 6, 0, &ft_do_motion_events, game);
