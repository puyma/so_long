/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:47:51 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/20 19:02:14 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int			ft_move(t_game *game, t_character *player, int keycode);
int			ft_toggle_pause(t_game *game);
int			ft_ismovable(t_game *game, t_character *character, t_vector *direction, int keycode);

int	ft_set_events(t_game *game)
{
	mlx_key_hook(game->mlx_window, &ft_keycode, game);
	mlx_mouse_hook(game->mlx_window, &ft_mousecode, game);
	mlx_hook(game->mlx_window, 17, 0, &ft_destroy, game);
	return (0);
}

int	ft_mousecode(int button, int x, int y, t_game *game)
{
	ft_printf("> button: %d, x: %d, y: %d\n", button, x, y);
	(void) game;
	return (0);
}

int	ft_keycode(int keycode, t_game *game)
{
	if (ft_ismovekey(keycode) != 0)
		ft_move(game, &game->player, keycode);
	else if (keycode == KEY_PAUSE)
		ft_toggle_pause(game);
	if (keycode == KEY_ESC)
		ft_destroy(game);
	return (0);
}

int	ft_move(t_game *game, t_character *player, int keycode)
{
	t_vector	direction;
	t_map_item	**arr;

	if (game->state != Running)
		return (0);
	if (ft_ismovable(game, &game->player, &direction, keycode) != 0)
	{
		arr = game->map->arr;
		arr[player->x][player->y].c = '0';
		arr[player->x + direction.x][player->y + direction.y].c = 'P';
	}
	ft_put_default_img(game, player->x, player->y);
	ft_put_default_img(game, player->x + direction.x, player->y + direction.y);

	ft_printf("> Move\n");
	return (0);
}

int	ft_ismovable(t_game *game, t_character *character, t_vector *direction, int keycode)
{
	int	move;

	move = ft_ismovekey(keycode);
	if (move == None)
		return (0);
	if (move == Left)
	{
		direction->x = 0;
		direction->y = -1;
	}
	else if (move == Right)
	{
		direction->x = 0;
		direction->y = 1;
	}
	else if (move == Up)
	{
		direction->x = -1;
		direction->y = 0;
	}
	else if (move == Down)
	{
		direction->x = 1;
		direction->y = 0;
	}
	if (game->map->arr[character->x + direction->x][character->y + direction->y].c == '1')
		return (0);
	else if (game->map->arr[character->x + direction->x][character->y + direction->y].c == 'C')
		ft_printf(">>f you\n");
	else if (game->map->arr[character->x + direction->x][character->y + direction->y].c == 'E')
		ft_printf(">>the end\n");
	return (1);
}

int	ft_toggle_pause(t_game *game)
{
	if (game->state != Paused)
	{
		ft_fill_window(game, game->i_blur);
		ft_put_img(game, game->i_pause, 0, game->width - game->size);
		game->state = Paused;
	}
	else
	{
		ft_put_images(game);
		game->state = Running;
	}
	ft_printf("> Pause\n");
	ft_log_state(game);
	return (0);
}

int	ft_destroy(t_game *game)
{
	mlx_clear_window(game->mlx, game->mlx_window);
	game->state = Stopping;
	ft_log_state(game);
	ft_printf("> Exit\n");
	mlx_destroy_window(game->mlx, game->mlx_window);
	game->state = Stopped;
	ft_log_state(game);
	exit(0);
	return (0);
}

void	ft_log_state(t_game *game)
{
	ft_printf("> state [%d]\n", game->state);
}
