/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 20:26:09 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/14 17:02:10 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

typedef struct s_button {
	int		width;
	int		height;
	int		x;
	int		y;
	void	*click_event;
	void	*hover_event;
}		t_button;

t_button	*ft_new_button(int w, int h, int x, int y);

t_button	*ft_new_button(int w, int h, int x, int y)
{
	t_button	*button;

	button = (t_button *) malloc(sizeof(t_button));
	if (button == NULL)
		return (NULL);
	button->width = w;
	button->height = h;
	button->x = x;
	button->y = y;
	return (button);
}

void	ft_mlx_pixel_put(t_imgdata *data, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = (y * data->line_length + x * (data->bits_per_pixel / 8));
	dst = data->address + offset;
	*(unsigned int *)dst = color;
}

/*
** Windows size needs to be checked before printing in order to not print where 
** cannot be printed (segmentation fault)
**
** There is this function in the mlx library: mlx_get_screen_size()
*/

/*
int	ft_draw_rectangle(int x, int y, int width, int height, t_imgdata *img)
{
	const int	x_max = x + width;
	const int	y_max = y + height;
	int			yy;

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
*/
