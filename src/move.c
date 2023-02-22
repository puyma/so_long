/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:00:55 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/22 10:20:57 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#define VEL 3

static int	ft_smooth_move_right(t_game *game, t_character *player, t_vector *direction);
static int	ft_smooth_move_left(t_game *game, t_character *player, t_vector *direction);
static int	ft_smooth_move_down(t_game *game, t_character *player, t_vector *direction);
static int	ft_smooth_move_up(t_game *game, t_character *player, t_vector *direction);

int	ft_move(t_game *game, t_character *player, int keycode)
{
	t_vector			direction;
	enum e_character	movable;

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
	ft_put_default_img(game, player->x, player->y);
	player->x += direction.x;
	player->y += direction.y;
	ft_put_default_img(game, player->x, player->y);
	mlx_do_sync(game->mlx);
	ft_printf("> Moves: %d\n", ++game->n_moves);
	return (0);
}

static int	ft_smooth_move_right(t_game *game, t_character *player, t_vector *direction)
{
	int	i;

	i = 1;
	while (i <= game->size)
	{
		ft_smoother_put_img(game, game->i_floor, player->x * game->size, player->y * game->size);
		ft_smoother_put_img(game, game->i_player, (player->x + direction->x) * game->size, (player->y * game->size) + i);
		mlx_do_sync(game->mlx);
		i += VEL;
	}
	return (0);
}

static int	ft_smooth_move_left(t_game *game, t_character *player, t_vector *direction)
{
	int	i;

	i = 1;
	while (i <= game->size)
	{
		ft_smoother_put_img(game, game->i_floor, player->x * game->size, player->y * game->size);
		ft_smoother_put_img(game, game->i_player, (player->x + direction->x) * game->size, (player->y * game->size) - i);
		mlx_do_sync(game->mlx);
		i += VEL;
	}
	return (0);
}

static int	ft_smooth_move_down(t_game *game, t_character *player, t_vector *direction)
{
	int	i;

	i = 1;
	while (i <= game->size)
	{
		ft_smoother_put_img(game, game->i_floor, player->x * game->size, player->y * game->size);
		ft_smoother_put_img(game, game->i_player, (player->x * game->size) + i, (player->y + direction->y) * game->size);
		mlx_do_sync(game->mlx);
		i += VEL;
	}
	return (0);
}

static int	ft_smooth_move_up(t_game *game, t_character *player, t_vector *direction)
{
	int	i;

	i = 1;
	while (i <= game->size)
	{
		ft_smoother_put_img(game, game->i_floor, player->x * game->size, player->y * game->size);
		ft_smoother_put_img(game, game->i_player, (player->x * game->size) - i, (player->y + direction->y) * game->size);
		mlx_do_sync(game->mlx);
		i += VEL;
	}
	return (0);
}
