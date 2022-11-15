/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_graphics.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:20:15 by mpuig-ma          #+#    #+#             */
/*   Updated: 2022/11/15 16:57:02 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

/*
int	ft_load_button(t_button *b, t_imgdata *img)
{
	ft_draw_rectangle(b->width, b->height, b->x, b->y, img);
	return (0);
}
*/
/*
int	ft_attach_event_to_button(t_button *b, int (*func)(void), t_game *game)
{
	(void) b;
	mlx_mouse_hook(game->mlx_window, *func, &game);
	return (0);
}
*/

int	ft_launch_graphics(void)
{
	t_game		game;
	t_imgdata	img;

	game.size = PIX_SIZE;
	game.height = PIX_SIZE * 10;
	game.width = PIX_SIZE * 10;
	game.mlx = mlx_init();
	game.mlx_window = mlx_new_window(game.mlx, game.width, game.height, "TDB");
	img.img = mlx_xpm_file_to_image(game.mlx, FLOOR, &img.width, &img.height);
	if (img.img == NULL)
	{
		ft_putstr("Error: ");
		ft_putendl_fd("Could not load image", 1);
		return (79);
	}
	else
		mlx_put_image_to_window(game.mlx, game.mlx_window, img.img, 0, 0);
	ft_set_events(&game);
	mlx_loop(game.mlx);
	return (0);
}

//img.img = mlx_new_image(game.mlx, DEF_WIDTH, DEF_HEIGHT);
//img.address = mlx_get_data_addr(img.img, &img.bits_per_pixel, 
//&img.line_length, &img.endian);
