/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:47:51 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/22 10:01:40 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_keyup(t_game *game)
{
	(void) game;
	return (0);
}

int	ft_set_events(t_game *game)
{
	mlx_hook(game->mlx_window, ON_KEYDOWN, 0, &ft_keycode, game);
	mlx_hook(game->mlx_window, ON_KEYUP, 0, &ft_keyup, game);
	mlx_hook(game->mlx_window, ON_DESTROY, 0, &ft_destroy, game);
	mlx_loop_hook(game->mlx, ft_state_render, game);
	return (0);
}

int	ft_state_render(t_game *game)
{
	mlx_do_sync(game->mlx);
	if (ft_the_end(game) != 0)
		ft_destroy(game);
	return (0);
}

int	ft_keycode(int keycode, t_game *game)
{
	if (ft_ismovekey(keycode) != 0)
		ft_move(game, &game->player, keycode);
	else if (keycode == KEY_PAUSE)
		ft_toggle_pause(game);
	if (keycode == KEY_ESC)
		ft_destroy(game);
	return (0);
}

int	ft_ismovable(t_game *game, t_character *character, t_vector *direction, int keycode)
{
	enum e_character	move;

	move = ft_ismovekey(keycode);
	if (move == None)
		return (0);
	if (move == Left)
	{
		direction->x = 0;
		direction->y = -1;
	}
	else if (move == Right)
	{
		direction->x = 0;
		direction->y = 1;
	}
	else if (move == Up)
	{
		direction->x = -1;
		direction->y = 0;
	}
	else if (move == Down)
	{
		direction->x = 1;
		direction->y = 0;
	}
	if (game->map->arr[character->x + direction->x][character->y + direction->y].c == '1')
		return (0);
	else if (game->map->arr[character->x + direction->x][character->y + direction->y].c == 'C')
		ft_putstr(">>f you\n");
	else if (game->map->arr[character->x + direction->x][character->y + direction->y].c == 'E')
		game->state = Stopping;
	return (move);
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
	ft_putstr("> Pause\n");
	ft_log_state(game);
	return (0);
}

int	ft_the_end(t_game *game)
{
	if (game->state == Stopping)
		return (1);
	return (0);
}

int	ft_destroy(t_game *game)
{
	mlx_clear_window(game->mlx, game->mlx_window);
	game->state = Stopping;
	ft_log_state(game);
	ft_putstr("> Exit\n");
	mlx_destroy_window(game->mlx, game->mlx_window);
	game->state = Stopped;
	ft_log_state(game);
	free(game->i_floor->img);
	free(game->i_wall->img);
	free(game->i_collectible->img);
	free(game->i_exit->img);
	free(game->i_player->img);
	free(game->i_blur->img);
	free(game->i_pause->img);
	free(game->map->lst);
	exit(0);
}
