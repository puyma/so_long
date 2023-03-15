/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:25:03 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/03/15 11:05:09 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_end(t_game *game);

#ifdef GENERATOR

// there may be a leak in here...

int	ft_keycode(int keycode, t_game *game)
{
	t_vector	*direction;

	if (keycode == KEY_ESC)
	{
		ft_write_map(game->filename, game->board);
		ft_destroy(game);
	}
	direction = ft_ismovekey(keycode);
	if (direction != NULL)
		ft_move(game, game->player, direction);
	if (keycode == KEY_1)
		game->board[game->player->x][game->player->y] = C_WALL;
	else if (keycode == KEY_0)
		game->board[game->player->x][game->player->y] = C_EMPTY_SPACE;
	else if (keycode == KEY_C)
		game->board[game->player->x][game->player->y] = C_COLLECTIBLE;
	else if (keycode == KEY_P)
		game->board[game->player->x][game->player->y] = C_PLAYER;
	else if (keycode == KEY_E)
		game->board[game->player->x][game->player->y] = C_EXIT;
	else if (keycode == KEY_N)
		game->board[game->player->x][game->player->y] = C_ENEMY;
	ft_put_default_img(game, game->player->x, game->player->y);
	ft_put_img(game, game->i_blur, game->player->x, game->player->y);
	return (0);
}

#else /* ifndef GENERATOR */

int	ft_keycode(int keycode, t_game *game)
{
	t_vector	*direction;

	if (keycode == KEY_ESC)
		return (ft_destroy(game));
	else if (keycode == KEY_PAUSE)
		return (ft_toggle_pause(game));
	direction = ft_ismovekey(keycode);
	if (direction != NULL)
		ft_move(game, game->player, direction);
	if (direction)
		free(direction);
	return (0);
}

#endif

int	ft_state_render(t_game *game)
{
	mlx_do_sync(game->mlx);
	if (game->state == Lost)
		ft_end(game);
	else if (game->state == Won)
		ft_end(game);
	if (game->state == Stopping)
		ft_destroy(game);
	else if (game->n_collectible == 0 && game->n_exit != 0)
	{
		ft_printf("You\'ve picked up all collectibles\n");
		game->board[game->exit->x][game->exit->y] = C_EXIT;
		ft_put_img(game, game->i_exit, game->exit->x, game->exit->y);
		game->n_exit = 0;
	}
	return (0);
}

static void	ft_end(t_game *game)
{
	if (game->state == Lost)
	{
		ft_fill_window(game, game->i_enemies[0]);
		mlx_do_sync(game->mlx);
		ft_printf("You\'ve lost...\n");
	}
	else if (game->state == Won)
	{
		ft_fill_window(game, game->i_exit);
		mlx_do_sync(game->mlx);
		ft_printf("You\'ve won with %u moves\n", game->n_moves);
	}
	game->state = Paused;
}

int	ft_destroy(t_game *game)
{
	mlx_clear_window(game->mlx, game->mlx_window);
	game->state = Stopping;
	ft_log_state(game->state);
	mlx_destroy_window(game->mlx, game->mlx_window);
	game->state = Stopped;
	ft_log_state(game->state);
	ft_memunload_images(game);
	ft_unload_board(game->board);
	free(game->map);
	exit(0);
}
