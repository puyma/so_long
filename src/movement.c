/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:41:09 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/03/02 15:41:10 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define VEL 4

#ifdef GENERATOR

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
	ft_put_default_img(game, player->x, player->y);
	ft_put_img(game, game->i_player, player->x + d->x, player->y + d->y);
	return (0);
}

#else

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

int	ft_set_direction(enum e_character move, t_vector *d)
{
	d->x = 0;
	d->y = 0;
	if (move == Left)
		d->y = -1;
	else if (move == Right)
		d->y = 1;
	else if (move == Up)
		d->x = -1;
	else if (move == Down)
		d->x = 1;
	return (move);
}
