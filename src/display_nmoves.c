/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_nmoves.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:13:19 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/03/13 16:49:01 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_display_nmoves(t_game *game, int background)
{
	(void) background;
	if (game->state == Won)
		return (0);
	if (game->n_moves == 1)
		ft_printf("%d move\n", game->n_moves);
	else
		ft_printf("%d moves\n", game->n_moves);
	return (0);
}
