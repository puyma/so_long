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

static int	ft_slide(t_game *game, t_character *player, t_vector *direction);
static int	ft_ismovable(t_game *game, t_character *character,
				t_vector *d, int keycode);
static int	ft_set_direction(enum e_character move, t_vector *d);

int	ft_move(t_game *game, t_character *player, int keycode)
{
	t_vector	direction;

	if (game->state != Running)
		return (0);
	if (ft_ismovable(game, &game->player, &direction, keycode) == 0)
		return (0);
	game->map->arr[player->x][player->y].c = '0';
	game->map->arr[player->x + direction.x][player->y + direction.y].c = 'P';
	ft_slide(game, player, &direction);
	ft_put_default_img(game, player->x, player->y);
	player->x += direction.x;
	player->y += direction.y;
	ft_put_default_img(game, player->x, player->y);
	mlx_do_sync(game->mlx);
	ft_printf("> Moves: %d\n", ++game->n_moves);
	return (0);
}

static int	ft_slide(t_game *game, t_character *player, t_vector *d)
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

static int	ft_ismovable(t_game *game, t_character *character,
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
	if (game->map->arr[cx][cy].c == '1')
		return (0);
	else if (game->map->arr[cx][cy].c == 'C')
		game->map->n_collectible--;
	else if (game->map->arr[cx][cy].c == 'E' && game->map->n_collectible == 0)
		game->state = Stopping;
	return (move);
}

int	ft_ismovekey(int keycode)
{
	enum e_character	direction;

	direction = None;
	if (keycode == KEY_UP || keycode == KEY_W)
		direction = Up;
	else if (keycode == KEY_DOWN || keycode == KEY_S)
		direction = Down;
	else if (keycode == KEY_RIGHT || keycode == KEY_D)
		direction = Right;
	else if (keycode == KEY_LEFT || keycode == KEY_A)
		direction = Left;
	return (direction);
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
