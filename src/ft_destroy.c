/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_destroy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:52:17 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/28 12:52:22 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	free(game->i_blur->img);
	free(game->i_pause->img);
	free(game->map->lst);
	exit(0);
}
