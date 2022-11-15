/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_pixel_put.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:52:59 by mpuig-ma          #+#    #+#             */
/*   Updated: 2022/10/27 18:45:39 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

void	ft_mlx_pixel_put(t_imgdata *data, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = (y * data->line_length + x * (data->bits_per_pixel / 8));
	dst = data->address + offset;
	*(unsigned int *)dst = color;
}
