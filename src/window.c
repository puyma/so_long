/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:19:02 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/03/10 15:19:48 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*ft_new_window(t_game *game, char *title)
{
	void	*window;

	window = mlx_new_window(game->mlx, game->width, game->height, title);
	return (window);
}

int	ft_fill_window(t_game *game, t_imgdata *img)
{
	int			x;
	int			y;

	x = 0;
	y = 0;
	while (game->board[x] != NULL)
	{
		y = 0;
		while (game->board[x][y] != '\0')
			ft_put_img(game, img, x, y++);
		x++;
	}
	return (0);
}
