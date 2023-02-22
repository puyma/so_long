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
#define VEL 4

static int	ft_slide(t_game *game, t_character *player, t_vector *direction);

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

int	ft_ismovable(t_game *game, t_character *character, t_vector *d, int keycode)
{
	enum e_character	move;

	move = ft_ismovekey(keycode);
	d->x = 0;
	d->y = 0;
	if (move == None)
		return (0);
	if (move == Left)
		d->y = -1;
	else if (move == Right)
		d->y = 1;
	else if (move == Up)
		d->x = -1;
	else if (move == Down)
		d->x = 1;
	if (game->map->arr[character->x + d->x][character->y + d->y].c == '1')
		return (0);
	else if (game->map->arr[character->x + d->x][character->y + d->y].c == 'C')
		ft_putstr(">>f you\n");
	else if (game->map->arr[character->x + d->x][character->y + d->y].c == 'E')
		game->state = Stopping;
	return (move);
}
