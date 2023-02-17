/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:47:51 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/17 18:57:48 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_move(t_game *game);
int	ft_toggle_pause(t_game *game);
int	ft_ismovable(t_game *game, t_character *character);
void	ft_log_state(t_game *game);

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
		ft_toggle_pause(game);
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
	if (game->state == Running && ft_ismovable(game, game->player) != 0)
	{
		ft_printf("> Move\n");
	}
	return (0);
}

int	ft_ismovable(t_game *game, t_character *character)
{
	(void) game;
	(void) character;
	return (1);
	return (0);
}

int	ft_toggle_pause(t_game *game)
{
	if (game->state != Paused)
	{
		ft_fill_window(game, game->i_blur);
		ft_put_img(game, game->i_pause, 0, game->width - game->size);
		game->state = Paused;
	}
	else
	{
		ft_put_images(game);
		game->state = Running;
	}
	ft_printf("> Pause\n");
	ft_log_state(game);
	return (0);
}

int	ft_destroy(t_game *game)
{
	game->state = Stopping;
	ft_log_state(game);
	ft_printf("> Exit\n");
	mlx_destroy_window(game->mlx, game->mlx_window);
	game->state = Stopped;
	ft_log_state(game);
	exit(0);
	return (0);
}

void	ft_log_state(t_game *game)
{
	ft_printf("> state [%d]\n", game->state);
}

//mlx_loop_hook(game->mlx, &ft_nothing, game);
//mlx_hook(game->mlx_window, 6, 0, &ft_do_motion_events, game);
