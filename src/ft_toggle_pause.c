/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toggle_pause.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:28:03 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/24 09:24:03 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_toggle_pause(t_game *game)
{
	if (game->state != Paused)
	{
		game->state = Paused;
		ft_fill_window(game, game->i_blur);
		ft_put_img(game, game->i_pause, 1, game->map->lnlen - 2);
	}
	else
	{
		game->state = Running;
		ft_put_images(game);
	}
	ft_log_state(game->state);
	return (0);
}