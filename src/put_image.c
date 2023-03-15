/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:30:30 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/03/10 15:33:05 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_put_images(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (game->board[x] != NULL)
	{
		y = 0;
		while (game->board[x][y] != '\0')
		{
			if (game->board[x][y] == C_EXIT && game->n_exit != 0)
				ft_put_img(game, game->i_floor, x, y);
			else if (game->board[x][y] == C_EXIT && game->n_exit == 0)
				ft_put_img(game, game->i_exit, x, y);
			else
				ft_put_default_img(game, x, y);
			y++;
		}
		x++;
	}
	return (0);
}

int	ft_put_default_img(t_game *game, int x, int y)
{
	if (game->board[x][y] == C_WALL)
		ft_put_img(game, game->i_wall, x, y);
	else if (game->board[x][y] == C_EMPTY_SPACE)
		ft_put_img(game, game->i_floor, x, y);
	else if (game->board[x][y] == C_COLLECTIBLE)
		ft_put_img(game, game->i_collectible, x, y);
	else if (game->board[x][y] == C_EXIT)
		ft_put_img(game, game->i_exit, x, y);
	else if (game->board[x][y] == C_PLAYER)
		ft_put_img(game, game->i_player, x, y);
	return (0);
}

int	ft_put_img(t_game *game, t_imgdata *img, int x, int y)
{
	x *= game->size;
	y *= game->size;
	mlx_put_image_to_window(game->mlx, game->mlx_window, img->img, y, x);
	return (0);
}

int	ft_put_img_xy(t_game *game, t_imgdata *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->mlx_window, img->img, y, x);
	return (0);
}
