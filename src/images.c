/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:20:15 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/21 16:58:50 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

int	ft_put_default_img(t_game *game, int x, int y)
{
	t_map_item	**arr;

	arr = game->map->arr;
	if (arr[x][y].c == '1')
		ft_put_img(game, game->i_wall, x, y);
	else if (arr[x][y].c == '0')
		ft_put_img(game, game->i_floor, x, y);
	else if (arr[x][y].c == 'C')
		ft_put_img(game, game->i_collectible, x, y);
	else if (arr[x][y].c == 'E')
		ft_put_img(game, game->i_exit, x, y);
	else if (arr[x][y].c == 'P')
	{
		ft_put_img(game, game->i_player, x, y);
		game->player.x = x;
		game->player.y = y;
	}
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
		{
			ft_put_img(game, img, x, y);
			y++;
		}
		x++;
	}
	return (0);
}
