/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_graphics.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:20:15 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/13 19:12:01 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

int	ft_preload_img(t_game *game);
int	ft_load_img(t_game *game);

int	ft_launch_graphics(t_map *map)
{
	t_game		game;
	t_imgdata	img;

	game.size = PIX_SIZE;
	game.width = map->lnlen * game.size;
	game.height = map->lstsize * game.size;
	game.mlx = mlx_init();
	game.mlx_window = mlx_new_window(game.mlx, game.width, game.height, "so_long");
	if (ft_preload_img(&game) != 0)
		ft_load_img(&game);
	img.img = mlx_xpm_file_to_image(game.mlx, FLOOR, &img.width, &img.height);
	if (img.img == NULL)
		ft_exit_str("Could not load image", 79);
	img.address = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	mlx_put_image_to_window(game.mlx, game.mlx_window, img.img, 10, 10);
	ft_set_events(&game);
	mlx_loop(game.mlx);
	return (0);
}

int	ft_preload_img(t_game *game)
{
	(void) game;
	return (1);
}

int	ft_load_img(t_game *game)
{
	(void) game;
	return (1);
}
