/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_nmoves.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:01:15 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/03/13 13:12:24 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_display_nmoves(t_game *game, int n, int background)
{
	int			x;
	int			y;
	int			digits;
	char		*itoa;

	if (LOG_LEVEL > 0)
		ft_printf("> Moves: %d\n", game->n_moves);
	x = game->height - (game->size / 2) + 3;
	y = (game->width - 1) / 2;
	digits = ft_count_digits(n, 10);
	if (background != 0)
	{
		ft_put_default_img(game, x / game->size, y / game->size);
		ft_put_default_img(game, x / game->size, (y + game->size) / game->size);
	}
	itoa = ft_itoa(n);
	mlx_string_put(game->mlx, game->mlx_window, y, x, 0x00F6CDAF, itoa);
	if (itoa)
		free(itoa);
	return (0);
}
