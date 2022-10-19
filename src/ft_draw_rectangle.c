/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_rectangle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 20:28:56 by mpuig-ma          #+#    #+#             */
/*   Updated: 2022/10/19 20:52:38 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

/*
** Windows size needs to be checked before printing in order to not print where 
** cannot be printed (segmentation fault)
**
** There is this function in the mlx library: mlx_get_screen_size()
*/

int	ft_draw_rectangle(int x, int y, int width, int height, t_data *img)
{
	const int	x_max = x + width;
	const int	y_max = y + height;
	int	yy;

	while (x <= x_max)
	{
		yy = y;
		while (yy <= y_max)
		{
			ft_mlx_pixel_put(img, x, yy, 0x000000CC);
			yy++;
		}
		x++;
	}
	return (0);
}
