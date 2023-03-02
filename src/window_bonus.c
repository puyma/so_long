/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:24:18 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/28 13:24:20 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*ft_new_window(t_game *game, char *title)
{
	void	*window;

	window = NULL;
	window = mlx_new_window(game->mlx, game->width, game->height, title);
	return (window);
}

int	ft_fill_window(t_game *game, t_imgdata *img)
{
	int			x;
	int			y;
	t_map_item	**arr;

	x = 0;
	y = 0;
	arr = game->map->arr;
	while (arr[x] != NULL)
	{
		y = 0;
		while (arr[x][y].c != '\0')
			ft_put_img(game, img, x, y++);
		x++;
	}
	return (0);
}
