/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_graphics.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:20:15 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/14 14:16:05 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

int			ft_memload_images(t_game *game);
t_imgdata	*ft_memload_img(t_game *game, char *filename);
int			ft_load_images(t_game *game);
int			ft_load_img(t_game *game, t_imgdata *img, int x, int y);
void		*ft_new_window(t_game *game, char *title);

int	ft_launch_graphics(t_map *map)
{
	t_game		game;

	game.size = PIX_SIZE;
	game.width = map->lstsize * game.size;
	game.height = map->lnlen * game.size;
	game.map = map;
	game.mlx = mlx_init();
	game.mlx_window = ft_new_window(&game, "so_long");
	if (ft_memload_images(&game) != 0)
		ft_load_images(&game);
	ft_set_events(&game);
	mlx_loop(game.mlx);
	return (0);
}

int	ft_load_images(t_game *game)
{
	t_map		*map;
	t_map_item	**arr;

	//int	img_x = 0;
	//int	img_y = 0;
	int	x = 0;
	int	y = 0;
	map = game->map;
	arr = map->arr;
	while (arr[x] != NULL)
	{
		y = 0;
		while (arr[x][y].c != '\0')
		{
			ft_printf("[%i][%i]:%c,", x, y, arr[x][y].c);
			if (arr[x][y].c == '1')
				ft_load_img(game, game->wall, x * game->size, y  * game->size);
			y++;
		}
		x++;
		write(1, "\n", 1);
	}
	return (0);
}

int	ft_load_img(t_game *game, t_imgdata *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->mlx_window, img->img, x, y);
	return (0);
}

void	*ft_new_window(t_game *game, char *title)
{
	void	*window;

	window = NULL;
	window = mlx_new_window(game->mlx, game->width, game->height, title);
	return (window);
}

int	ft_memload_images(t_game *game)
{
	game->floor = ft_memload_img(game, FLOOR);
	game->wall = ft_memload_img(game, WALL);
	game->collectible = ft_memload_img(game, COLLECTIBLE);
	game->exit = ft_memload_img(game, EXIT);
	game->player = ft_memload_img(game, PLAYER);
	return (1);
}

t_imgdata	*ft_memload_img(t_game *game, char *filename)
{
	t_imgdata	*img;

	img = (t_imgdata *) ft_calloc(sizeof(t_imgdata), 1);
	img->img = mlx_xpm_file_to_image(game->mlx, filename, \
			&img->width, &img->height);
	if (img->img == NULL)
		ft_exit_str("Could not load image", 79);
	img->address = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
			&img->line_length, &img->endian);
	return (img);
}
