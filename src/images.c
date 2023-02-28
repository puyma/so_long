/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:20:15 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/24 09:18:14 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_set_character(t_game *game, int x, int y);

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
			if (arr[x][y].c == C_PLAYER || arr[x][y].c == C_EXIT)
				ft_set_character(game, x, y);
			if (arr[x][y].c == C_EXIT)
				ft_put_img(game, game->i_floor, x, y);
			else
				ft_put_default_img(game, x, y);
			y++;
		}
		x++;
	}
	return (0);
}

static int	ft_set_character(t_game *game, int x, int y)
{
	int	c;

	c = game->map->arr[x][y].c;
	if (c == C_EXIT)
	{
		game->map->exit->x = x;
		game->map->exit->y = y;
	}
	else if (c == C_PLAYER)
	{
		game->map->player->x = x;
		game->map->player->y = y;
	}
	return (0);
}

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
