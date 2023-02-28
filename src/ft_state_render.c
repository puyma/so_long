/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_state_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:47:51 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/24 11:12:34 by mpuig-ma         ###   ########.fr       */
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
