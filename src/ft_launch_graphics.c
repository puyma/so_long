/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_graphics.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:20:15 by mpuig-ma          #+#    #+#             */
/*   Updated: 2022/10/19 20:14:48 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

int	ft_launch_graphics(void)
{
	t_game	game;
	t_data	img;

	game.mlx = mlx_init();
	game.mlx_window = mlx_new_window(game.mlx, DEF_WIDTH, DEF_HEIGHT, "TDB");

	img.img = mlx_new_image(game.mlx, DEF_WIDTH, DEF_HEIGHT);
	img.address = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	// start button
	int x_center = DEF_WIDTH / 2;
	int y_center = DEF_HEIGHT / 2;
	int	button_width = 210;
	int	button_height = 40;
	int x = x_center - (button_width / 2);
	int y = y_center - (button_height / 2);
	while (button_width > 0)
	{
		y = y_center - (button_height / 2);
		button_height = 40;
		y = (DEF_HEIGHT / 2) - button_height;
		while (button_height > 0)
		{
			ft_mlx_pixel_put(&img, x, y, 0x000000CC);
			button_height--;
			y++;
		}
		x++;
		button_width--;
	}

	mlx_put_image_to_window(game.mlx, game.mlx_window, img.img, 0, 0);

	mlx_put_image_to_window(game.mlx, game.mlx_window, img.img, 0, 0);
	//mlx_loop_hook(game.mlx, &ft_nothing, &game);
	mlx_key_hook(game.mlx_window, &ft_keycode, &game);
	mlx_mouse_hook(game.mlx_window, &ft_mousecode, &game);
	mlx_hook(game.mlx_window, 17, 0, &ft_destroy, &game);
	mlx_loop(game.mlx);
	return (0);
}
