/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:30:38 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/24 09:44:15 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_keycode(int keycode, t_game *game)
{
	if (ft_ismovekey(keycode) != 0)
		ft_move(game, &game->player, keycode);
	else if (keycode == KEY_PAUSE)
		ft_toggle_pause(game);
	if (keycode == KEY_ESC)
		ft_destroy(game);
	return (0);
}
