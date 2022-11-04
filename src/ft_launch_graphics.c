/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_graphics.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:20:15 by mpuig-ma          #+#    #+#             */
/*   Updated: 2022/11/04 18:38:35 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

t_button	*ft_new_button(int w, int h, int x, int y)
{
	t_button	*button;

	button = (t_button *) malloc(sizeof(t_button));
	if (button == NULL)
		return (NULL);
	button->width = w;
	button->height = h;
	button->x = x;
	button->y = y;
	return (button);
}

int	ft_load_button(t_button *b, t_data *img)
{
	ft_draw_rectangle(b->width, b->height, b->x, b->y, img);
	return (0);
}

int	ft_attach_event_to_button(t_button *b, int (*func)(void), t_game *game)
{
	(void) b;
	mlx_mouse_hook(game->mlx_window, *func, &game);
	return (0);
}

int	ft_launch_graphics(void)
{
	t_game	game;
	t_data	img;
	t_list	buttons;

	game.mlx = mlx_init();
	game.mlx_window = mlx_new_window(game.mlx, DEF_WIDTH, DEF_HEIGHT, "TDB");

	img.img = mlx_new_image(game.mlx, DEF_WIDTH, DEF_HEIGHT);
	img.address = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	ft_lstnew();

	// start button
	t_button *start_button;
	start_button = ft_new_button(200, 200, 300, 300);
	start_button->click_event = ft_test;
	ft_attach_event_to_button(start_button, ft_test, &game);
	ft_load_button(start_button, &img);

	//ft_draw_rectangle(200, 200, 300, 300, &img);
	mlx_put_image_to_window(game.mlx, game.mlx_window, img.img, 0, 0);

	mlx_put_image_to_window(game.mlx, game.mlx_window, img.img, 0, 0);
	//mlx_loop_hook(game.mlx, &ft_nothing, &game);
	mlx_key_hook(game.mlx_window, &ft_keycode, &game);
	//mlx_mouse_hook(game.mlx_window, &ft_mousecode, &game);
	mlx_hook(game.mlx_window, 6, 0, &ft_nothing, &game);
	mlx_hook(game.mlx_window, 17, 0, &ft_destroy, &game);

	mlx_loop(game.mlx);
	return (0);
}
