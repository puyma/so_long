/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:20:15 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/20 10:26:14 by mpuig-ma         ###   ########.fr       */
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

int	ft_memload_images(t_game *game)
{
	game->i_floor = ft_memload_img(game, FLOOR);
	game->i_wall = ft_memload_img(game, WALL);
	game->i_collectible = ft_memload_img(game, COLLECTIBLE);
	game->i_exit = ft_memload_img(game, EXIT);
	game->i_player = ft_memload_img(game, PLAYER);
	game->i_blur = ft_memload_img(game, BLUR);
	game->i_pause = ft_memload_img(game, PAUSE);
	return (1);
}

t_imgdata	*ft_memload_img(t_game *game, char *filename)
{
	t_imgdata	*img;

	img = (t_imgdata *) ft_calloc(sizeof(t_imgdata), 1);
	if (ft_filext_isvalid(filename, ".xpm") != 0)
		img->img = mlx_xpm_file_to_image(game->mlx, filename, \
			&img->width, &img->height);
	else if (ft_filext_isvalid(filename, ".png") != 0)
		img->img = mlx_png_file_to_image(game->mlx, filename, \
			&img->width, &img->height);
	else
		exit(69);
	if (img->img == NULL)
		ft_exit_str("Could not load image", 79);
	img->address = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
			&img->line_length, &img->endian);
	return (img);
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
