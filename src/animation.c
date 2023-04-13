/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:51:41 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/03/13 11:45:50 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#define VEL 2

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
		ft_put_img_xy(game, game->i_floor, px, py);
		ft_put_img_xy(game, game->i_player, px + (i * d->x), py + (i * d->y));
		mlx_do_sync(game->mlx);
		i += VEL;
	}
	return (0);
}

#endif

void	ft_animate_player(t_game *game, t_vector *player, t_vector *d)
{
	static int	px = 0;
	static int	py = 0;
	static int	x_to = 0;
	static int	y_to = 0;
	static int	dx = 0;
	static int	dy = 0;
	static int	lock = 0;

	if (d != NULL && lock == 0)
	{
		px = player->x * game->size;
		py = player->y * game->size;
		x_to = px + (game->size * d->x);
		y_to = py + (game->size * d->y);
		dx = d->x;
		dy = d->y;
		lock = 1;
	}
	if (d == NULL && px == x_to && py == y_to && lock == 1)
	{
		dx = 0;
		dy = 0;
		lock = 0;
	}
	if ((dx != 0 || dy != 0) && lock == 1)
	{
		ft_put_img_xy(game, game->i_floor, px, py);
		px += dx * VEL;
		py += dy * VEL;
		ft_put_img_xy(game, game->i_player, px, py);
		mlx_do_sync(game->mlx);
	}
}
