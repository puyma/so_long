/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ismovekey.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:38:27 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/28 14:38:29 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_ismovekey(int keycode)
{
	enum e_character	direction;

	direction = None;
	if (keycode == KEY_UP || keycode == KEY_W)
		direction = Up;
	else if (keycode == KEY_DOWN || keycode == KEY_S)
		direction = Down;
	else if (keycode == KEY_RIGHT || keycode == KEY_D)
		direction = Right;
	else if (keycode == KEY_LEFT || keycode == KEY_A)
		direction = Left;
	return (direction);
}
