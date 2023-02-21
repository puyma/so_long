/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:47:51 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/21 13:06:38 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int			ft_move(t_game *game, t_character *player, int keycode);
int			ft_smoother_move(t_game *game, t_character *player, int keycode);
int			ft_smooth_move_right(t_game *game, t_character *player, t_vector *direction);
int			ft_smooth_move_left(t_game *game, t_character *player, t_vector *direction);
int			ft_smooth_move_down(t_game *game, t_character *player, t_vector *direction);
int			ft_smooth_move_up(t_game *game, t_character *player, t_vector *direction);
int			ft_toggle_pause(t_game *game);
int			ft_ismovable(t_game *game, t_character *character, t_vector *direction, int keycode);
int			ft_the_end(t_game *game);
int			ft_hey(t_game *game);

int	ft_set_events(t_game *game)
{
	mlx_do_key_autorepeaton(game->mlx);
	mlx_key_hook(game->mlx_window, &ft_keycode, game);
	mlx_mouse_hook(game->mlx_window, &ft_mousecode, game);
	mlx_hook(game->mlx_window, 17, 0, &ft_destroy, game);
	mlx_loop_hook(game->mlx, ft_hey, game);
	return (0);
}

int	ft_hey(t_game *game)
{
	mlx_do_sync(game->mlx);
	if (ft_the_end(game) != 0)
		ft_destroy(game);
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
		ft_smoother_move(game, &game->player, keycode);
	else if (keycode == KEY_PAUSE)
		ft_toggle_pause(game);
	if (keycode == KEY_ESC)
		ft_destroy(game);
	return (0);
}

int	ft_move(t_game *game, t_character *player, int keycode)
{
	t_vector	direction;

	if (game->state != Running)
		return (0);
	if (ft_ismovable(game, &game->player, &direction, keycode) == 0)
		return (0);
	game->map->arr[player->x][player->y].c = '0';
	game->map->arr[player->x + direction.x][player->y + direction.y].c = 'P';
	ft_put_default_img(game, player->x, player->y);
	ft_put_default_img(game, player->x + direction.x, player->y + direction.y);
	ft_printf("> Moves: %d\n", ++game->n_moves);
	return (0);
}

int	ft_smoother_move(t_game *game, t_character *player, int keycode)
{
	t_vector	direction;
	int			movable;

	if (game->state != Running)
		return (0);
	movable = ft_ismovable(game, &game->player, &direction, keycode);
	if (movable == None)
		return (0);
	game->map->arr[player->x][player->y].c = '0';
	game->map->arr[player->x + direction.x][player->y + direction.y].c = 'P';
	if (movable == Right)
		ft_smooth_move_right(game, player, &direction);
	else if (movable == 1)
		ft_smooth_move_left(game, player, &direction);
	else if (movable == Down)
		ft_smooth_move_down(game, player, &direction);
	else if (movable == Up)
		ft_smooth_move_up(game, player, &direction);
	player->x += direction.x;
	player->y += direction.y;
	ft_put_default_img(game, player->x + direction.x, player->y + direction.y);
	ft_printf("> Moves: %d\n", ++game->n_moves);
	return (0);
}

int	ft_smooth_move_right(t_game *game, t_character *player, t_vector *direction)
{
	int	i;

	i = 1;
	while (i <= game->size)
	{
		ft_smoother_put_img(game, game->i_floor, player->x * game->size, player->y * game->size);
		ft_smoother_put_img(game, game->i_player, (player->x + direction->x) * game->size, (player->y * game->size) + i);
		mlx_do_sync(game->mlx);
		i++;
	}
	return (0);
}

int	ft_smooth_move_left(t_game *game, t_character *player, t_vector *direction)
{
	int	i;

	i = 1;
	while (i <= game->size)
	{
		ft_smoother_put_img(game, game->i_floor, player->x * game->size, player->y * game->size);
		ft_smoother_put_img(game, game->i_player, (player->x + direction->x) * game->size, (player->y * game->size) - i);
		mlx_do_sync(game->mlx);
		i++;
	}
	return (0);
}

int	ft_smooth_move_down(t_game *game, t_character *player, t_vector *direction)
{
	int	i;

	i = 1;
	while (i <= game->size)
	{
		ft_smoother_put_img(game, game->i_floor, player->x * game->size, player->y * game->size);
		ft_smoother_put_img(game, game->i_player, (player->x * game->size) + i, (player->y + direction->y) * game->size);
		mlx_do_sync(game->mlx);
		i++;
	}
	return (0);
}

int	ft_smooth_move_up(t_game *game, t_character *player, t_vector *direction)
{
	int	i;

	i = 1;
	while (i <= game->size)
	{
		ft_smoother_put_img(game, game->i_floor, player->x * game->size, player->y * game->size);
		ft_smoother_put_img(game, game->i_player, (player->x * game->size) - i, (player->y + direction->y) * game->size);
		mlx_do_sync(game->mlx);
		i++;
	}
	return (0);
}

int	ft_ismovable(t_game *game, t_character *character, t_vector *direction, int keycode)
{
	enum e_character	move;

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
		game->state = Stopping;
	return (move);
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

int	ft_the_end(t_game *game)
{
	if (game->state == Stopping)
		return (1);
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
