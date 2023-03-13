/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:52:46 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/03/13 16:59:14 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// need to do something with: end game

int	ft_move_able(t_game *game, t_vector *player, t_vector *d)
{
	int	cx;
	int	cy;

	cx = player->x + d->x;
	cy = player->y + d->y;
	if (game->board[cx][cy] == C_WALL)
		return (0);
	else if (game->board[cx][cy] == C_COLLECTIBLE)
	{
		game->n_collectible--;
		if (game->n_collectible > 1)
			ft_printf("%d items remaining\n",
				game->n_collectible);
		else if (game->n_collectible == 1)
			ft_printf("%d item remaining\n", game->n_collectible);
	}
	else if (game->board[cx][cy] == C_EXIT
		&& game->n_collectible == 0)
		game->state = Won;
	return (1);
}

// do not display moves if generator is set

int	ft_move(t_game *game, t_vector *player, t_vector *d)
{
	if (game->state != Running)
		return (0);
	if (ft_move_able(game, player, d) == 0)
		return (0);
	game->board[player->x][player->y] = C_EMPTY_SPACE;
	game->board[player->x + d->x][player->y + d->y] = C_PLAYER;
	ft_slide(game, player, d);
	ft_put_default_img(game, player->x, player->y);
	player->x += d->x;
	player->y += d->y;
	ft_put_default_img(game, player->x, player->y);
	mlx_do_sync(game->mlx);
	game->n_moves++;
	ft_display_nmoves(game, 0);
	return (0);
}

t_vector	*ft_ismovekey(int keycode)
{
	t_vector	*direction;

	direction = ft_calloc(1, sizeof(t_vector));
	if (direction == NULL)
		return (NULL);
	direction->x = 0;
	direction->y = 0;
	if (keycode == KEY_UP || keycode == KEY_W)
		direction->x = -1;
	else if (keycode == KEY_DOWN || keycode == KEY_S)
		direction->x = 1;
	else if (keycode == KEY_RIGHT || keycode == KEY_D)
		direction->y = 1;
	else if (keycode == KEY_LEFT || keycode == KEY_A)
		direction->y = -1;
	if (direction->x == 0 && direction->y == 0)
	{
		free(direction);
		direction = NULL;
	}
	return (direction);
}
