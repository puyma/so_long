/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:00:55 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/24 09:18:48 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_ismovable(t_game *game, t_vector *character,
				t_vector *d, int keycode);

// t_vector d -> direction

#ifdef GENERATOR

int	ft_move(t_game *game, t_vector *player, int keycode)
{
	t_vector	d;

	if (game->state != Running)
		return (0);
	if (ft_ismovable(game, game->map->player, &d, keycode) == 0)
		return (0);
	ft_slide(game, player, &d);
	player->x += d.x;
	player->y += d.y;
	ft_put_default_img(game, player->x, player->y);
	mlx_do_sync(game->mlx);
	ft_printf("> Moves: %d\n", ++game->n_moves);
	return (0);
}

#else

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
	ft_display_nmoves(game, ++game->n_moves, 1);
	return (0);
}

#endif

int	ft_display_nmoves(t_game *game, int n, int background)
{
	int			x;
	int			y;
	int			digits;

	if (LOG_LEVEL > 0)
		ft_printf("> Moves: %d\n", game->n_moves);
	x = game->height - (game->size / 2) + 3;
	y = (game->width - 1) / 2;
	digits = ft_count_digits(n, 10);
	if (background != 0)
	{
		ft_put_default_img(game, x / game->size, y / game->size);
		ft_put_default_img(game, x / game->size, (y + game->size) / game->size);
	}
	mlx_string_put(game->mlx, game->mlx_window, y, x, 0x00F6CDAF, ft_itoa(n));
	return (0);
}

#ifdef GENERATOR

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
	(void) game;
	return (move);
}

#else

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
		game->state = Ended;
	return (move);
}

#endif
