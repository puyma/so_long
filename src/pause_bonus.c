/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:20:29 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/03/10 15:20:50 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// only for bonus / generator

int	ft_toggle_pause(t_game *game)
{
	if (game->state != Paused && game->state != Running)
		return (0);
	if (game->state != Paused)
	{
		game->state = Paused;
		ft_fill_window(game, game->i_blur);
		ft_put_img(game, game->i_pause, 0, (game->width - 1) / game->size);
	}
	else
	{
		game->state = Running;
		ft_put_images(game);
	}
	ft_display_nmoves(game, game->n_moves, 0);
	ft_log_state(game->state);
	return (0);
}
