/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_images_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:20:15 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/24 09:18:14 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#ifdef GENERATOR

int	ft_put_images(t_game *game)
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
			ft_put_default_img(game, x, y++);
		x++;
	}
	return (0);
}

#else /* ifndef GENERATOR */

int	ft_put_images(t_game *game)
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
		{
			if (arr[x][y].c == C_EXIT && game->map->n_exit != 0)
				ft_put_img(game, game->i_floor, x, y);
			else if (arr[x][y].c == C_EXIT && game->map->n_exit == 0)
				ft_put_img(game, game->i_exit, x, y);
			else
				ft_put_default_img(game, x, y);
			y++;
		}
		x++;
	}
	return (0);
}

#endif

int	ft_put_default_img(t_game *game, int x, int y)
{
	t_map_item	**arr;

	arr = game->map->arr;
	if (arr[x][y].c == C_WALL)
		ft_put_img(game, game->i_wall, x, y);
	else if (arr[x][y].c == C_EMPTY_SPACE)
		ft_put_img(game, game->i_floor, x, y);
	else if (arr[x][y].c == C_COLLECTIBLE)
		ft_put_img(game, game->i_collectible, x, y);
	else if (arr[x][y].c == C_EXIT)
		ft_put_img(game, game->i_exit, x, y);
	else if (arr[x][y].c == C_PLAYER)
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
