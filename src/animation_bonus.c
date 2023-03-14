/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:51:41 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/03/14 13:16:20 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#define VEL 4

#ifdef GENERATOR

int	ft_slide(t_game *game, t_vector *player, t_vector *d)
{
	ft_put_default_img(game, player->x, player->y);
	ft_put_img(game, game->i_player, player->x + d->x, player->y + d->y);
	return (0);
}

#else /* ifndef GENERATOR */

int	ft_slide(t_game *game, t_vector *player, t_vector *d)
{
	int	size;
	int	px;
	int	py;
	int	i;

	size = game->size;
	px = player->x * size;
	py = player->y * size;
	i = 1;
	while (i <= size)
	{
		ft_animate_enemy(game);
		ft_put_img_xy(game, game->i_floor, px, py);
		ft_put_img_xy(game, game->i_player, px + (i * d->x), py + (i * d->y));
		mlx_do_sync(game->mlx);
		i += VEL;
	}
	return (0);
}

#endif

void	ft_animate_player(t_game *game)
{

}

// aka ft_next_enemy

void	ft_animate_enemy(t_game *game)
{
	t_vector	*enemy;
	static int	wait = 0;
	const int	max = 10;
	static int	i = 0;

	if (i == max)
	{
		wait = 133;
		i = 0;
	}
	else if (wait > 0)
		wait--;
	else if (i < max)
	{
		ft_put_img(game, game->i_enemies[i], enemy->x, enemy->y);
		i++;
	}
}
