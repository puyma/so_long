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

static int	ft_ismovable(t_game *game, t_vector *character,
				t_vector *d, int keycode);

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
	ft_printf("> Moves: %d\n", ++game->n_moves);
	return (0);
}

static int	ft_ismovable(t_game *game, t_vector *character,
				t_vector *d, int keycode)
{
	enum e_character	move;
	size_t				cx;
	size_t				cy;

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
		ft_ended(game);
	return (move);
}
