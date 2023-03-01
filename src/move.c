/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:00:55 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/24 09:18:48 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#define VEL 4

static int	ft_slide(t_game *game, t_vector *player, t_vector *d);
static int	ft_ismovable(t_game *game, t_vector *character,
				t_vector *d, int keycode);
static int	ft_set_direction(enum e_character move, t_vector *d);

// t_vector d -> direction

int	ft_move(t_game *game, t_vector *player, int keycode)
{
	t_vector	d;

	if (game->state != Running)
		return (0);
	if (ft_ismovable(game, game->map->player, &d, keycode) == 0)
		return (0);
	game->map->arr[player->x][player->y].c = C_EMPTY_SPACE;
	game->map->arr[player->x + d.x][player->y + d.y].c = C_PLAYER;
	ft_slide(game, player, &d);
	ft_put_default_img(game, player->x, player->y);
	player->x += d.x;
	player->y += d.y;
	ft_put_default_img(game, player->x, player->y);
	mlx_do_sync(game->mlx);
	ft_display_nmoves(game, ++game->n_moves);
	return (0);
}

int	ft_display_nmoves(t_game *game, int n)
{
	int			x;
	int			y;
	int			digits;
	
	ft_printf("> Moves: %d\n", game->n_moves);
	x = game->height - (game->size / 2) + 3;
	y = (game->width - 1) / 2;
	digits = ft_count_digits(n, 10);
	ft_put_default_img(game, x / game->size, y / game->size);
	ft_put_default_img(game, x / game->size, (y + game->size) / game->size);
	mlx_string_put(game->mlx, game->mlx_window, y, x, 0x00F6CDAF, ft_itoa(n));
	return (0);
}

static int	ft_slide(t_game *game, t_vector *player, t_vector *d)
{
	int	size;
	int	px;
	int	py;
	int	i;

	size = game->size;
	px = player->x * size;
	py = player->y * size;
	i = 1;
	while (i <= size)
	{
		ft_put_img_xy(game, game->i_floor, px, py);
		ft_put_img_xy(game, game->i_player, px + (i * d->x), py + (i * d->y));
		mlx_do_sync(game->mlx);
		i += VEL;
	}
	return (0);
}

static int	ft_ismovable(t_game *game, t_vector *character,
				t_vector *d, int keycode)
{
	enum e_character	move;
	int					cx;
	int					cy;

	move = ft_ismovekey(keycode);
	if (move == None)
		return (0);
	ft_set_direction(move, d);
	cx = character->x + d->x;
	cy = character->y + d->y;
	if (game->map->arr[cx][cy].c == C_WALL)
		return (0);
	else if (game->map->arr[cx][cy].c == C_COLLECTIBLE)
		game->map->n_collectible--;
	else if (game->map->arr[cx][cy].c == C_EXIT
		&& game->map->n_collectible == 0)
		game->state = Stopping;
	return (move);
}

static int	ft_set_direction(enum e_character move, t_vector *d)
{
	d->x = 0;
	d->y = 0;
	if (move == Left)
		d->y = -1;
	else if (move == Right)
		d->y = 1;
	else if (move == Up)
		d->x = -1;
	else if (move == Down)
		d->x = 1;
	return (move);
}
