/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:47:51 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/13 19:07:47 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

int	ft_destroy(t_game *game)
{
	mlx_destroy_window(game->mlx, game->mlx_window);
	write(1, "> Exiting...\n", 13);
	exit(0);
	return (0);
}

int	ft_keycode(int keycode, t_game *game)
{
	(void) game;
	write(1, "> key: ", 7);
	if (keycode == KEY_UP)
		ft_putstr("↑");
	else if (keycode == KEY_DOWN)
		ft_putstr("↓");
	else if (keycode == KEY_LEFT)
		ft_putstr("←");
	else if (keycode == KEY_RIGHT)
		ft_putstr("→");
	else
		ft_putnbr(keycode);
	write(1, "\n", 1);
	if (keycode == KEY_ESC)
	{
		mlx_clear_window(game->mlx, game->mlx_window);
		ft_destroy(game);
	}
	return (0);
}

int	ft_mousecode(int button, int x, int y, t_game *game)
{
	ft_printf("button: %d, x: %d, y: %d\n", button, x, y);
	(void) game;
	return (0);
}

int	ft_set_events(t_game *game)
{
	mlx_key_hook(game->mlx_window, &ft_keycode, game);
	mlx_mouse_hook(game->mlx_window, &ft_mousecode, game);
	mlx_hook(game->mlx_window, 17, 0, &ft_destroy, game);
	return (0);
}

//mlx_loop_hook(game->mlx, &ft_nothing, game);
//mlx_hook(game->mlx_window, 6, 0, &ft_do_motion_events, game);

/*
int	ft_do_motion_events(int x, int y, t_game *game)
{
	t_list		*button_node;
	t_button	*button;

	button_node = *(game->buttons);
	while (button_node != NULL)
	{
		button = button_node->content;
		//ft_printf("mousemove> X: %d, Y: %d\n", x, y);
		if (button->x <= x && x <= button->x + button->width)
		{
			//if (button->y <= y && y <= button->y + button->height)
			(void) y;
			write(1, "Clickitty\n", 10);
		}
		button_node = button_node->next;
	}
	return (0);
}
*/
