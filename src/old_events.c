/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:12:07 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/03/02 12:12:08 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_state_render(t_game *game)
{
	mlx_do_sync(game->mlx);
	if (game->state == Stopping)
		ft_destroy(game);
	else if (game->map->n_collectible == 0 && game->map->n_exit != 0)
	{
		ft_log("Obtained all collectibles");
		game->map->arr[game->map->exit->x][game->map->exit->y].c = C_EXIT;
		ft_put_img(game, game->i_exit, game->map->exit->x, game->map->exit->y);
		game->map->n_exit = 0;
	}
	return (0);
}

int	ft_destroy(t_game *game)
{
	mlx_clear_window(game->mlx, game->mlx_window);
	game->state = Stopping;
	ft_log_state(game->state);
	mlx_destroy_window(game->mlx, game->mlx_window);
	game->state = Stopped;
	ft_log_state(game->state);
	free(game->i_floor->img);
	free(game->i_wall->img);
	free(game->i_collectible->img);
	free(game->i_exit->img);
	free(game->i_player->img);
	free(game->map->lst);
	exit(0);
}

int	ft_ended(t_game *game)
{
	game->state = Ended;
	return (0);
}

int	ft_keycode(int keycode, t_game *game)
{
	if (ft_ismovekey(keycode) != 0)
		ft_move(game, game->map->player, keycode);
	else if (keycode == KEY_ESC)
		ft_destroy(game);
	return (0);
}