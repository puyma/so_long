/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:27:40 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/03/13 15:46:26 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_launch(t_game *game)
{
	if (ft_memload_images(game) == 0)
		ft_exit("Could not allocate memory", 8, NULL, NULL);
	ft_put_images(game);
	mlx_hook(game->mlx_window, ON_DESTROY, 0, &ft_destroy, game);
	mlx_hook(game->mlx_window, ON_KEYDOWN, 0, &ft_keycode, game);
	mlx_loop_hook(game->mlx, &ft_state_render, game);
	game->state = Running;
	mlx_loop(game->mlx);
	return (0);
}
