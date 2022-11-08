/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_graphics.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:20:15 by mpuig-ma          #+#    #+#             */
/*   Updated: 2022/11/08 17:22:33 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

int	ft_load_button(t_button *b, t_data *img)
{
	ft_draw_rectangle(b->width, b->height, b->x, b->y, img);
	return (0);
}

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
	t_game	game;
	t_data	img;

	game.size = PIX_SIZE;

	game.mlx = mlx_init();
	game.mlx_window = mlx_new_window(game.mlx, DEF_WIDTH, DEF_HEIGHT, "TDB");

	//img.img = mlx_new_image(game.mlx, DEF_WIDTH, DEF_HEIGHT);
	//img.address = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	/*
	t_button *start_button;
	start_button = ft_new_button(200, 200, 300, 300);
	start_button->click_event = ft_test;
	t_list *node = ft_lstnew(start_button); // t_button should go inside t_list->content
	game.buttons = &node;

	t_button *secondary_button;
	secondary_button = ft_new_button(42, 42, 200, 340);
	node = ft_lstnew(secondary_button);
	ft_lstadd_back(game.buttons, node);
	*/

	/*
	ft_attach_event_to_button(start_button, ft_test, &game);
	*/

	/*
	ft_load_button(start_button, &img);
	ft_load_button(secondary_button, &img);
	*/

	int	height = 0;
	int width = 0;

	img.img = mlx_xpm_file_to_image(game.mlx, "../src/suelo.xpm", &width, &height);
	if (img.img == NULL)
		write(1, "Fuck, is null\n", 14);
	else
	{
		img.address = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
		mlx_put_image_to_window(game.mlx, game.mlx_window, img.img, 0, 0);
	}

	ft_set_events(&game);
	mlx_loop(game.mlx);
	return (0);
}
