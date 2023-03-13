/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:22:21 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/03/13 12:03:19 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_solve(t_game *game, size_t x, size_t y, int **board);
static int	ft_clear_path(int **board, int **pathfinding);

int	ft_check_path(t_game *game)
{
	int			**board;
	t_list		*l;
	t_vector	*v;

	ft_log("Searching for a valid path...");
	board = ft_new_board(game->map->width, game->map->height);
	ft_clear_path(game->board, board);
	l = game->collectibles;
	if (ft_solve(game, game->player->x, game->player->y, board) == 0)
		return (ft_unload_board(board));
	while (l != NULL)
	{
		v = l->content;
		ft_clear_path(game->board, board);
		if (ft_solve(game, v->x, v->y, board) == 0)
			return (ft_unload_board(board));
		l = l->next;
	}
	ft_unload_board(board);
	return (1);
}

static int	ft_solve(t_game *game, size_t x, size_t y, int **board)
{
	if (x == (size_t) game->exit->x && y == (size_t) game->exit->y)
	{
		if (LOG_LEVEL > 0)
			ft_printf("> Reached exit: %d, %d\n", x, y);
		return (1);
	}
	if (x >= game->map->height || y >= game->map->width)
		return (0);
	if (board[x][y] == 1)
		return (0);
	board[x][y] = 1;
	if (LOG_LEVEL > 0)
		ft_printf("> visited: %u, %u\n", x, y);
	if (ft_solve(game, x, y + 1, board))
		return (1);
	if (ft_solve(game, x + 1, y, board))
		return (1);
	if (ft_solve(game, x, y - 1, board))
		return (1);
	if (ft_solve(game, x - 1, y, board))
		return (1);
	board[x][y] = 0;
	return (0);
}

static int	ft_clear_path(int **board, int **pathfinding)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (board[x] != NULL)
	{
		y = 0;
		while (board[x][y] != '\0')
		{
			if (board[x][y] == C_WALL)
				pathfinding[x][y] = 1;
			else
				pathfinding[x][y] = 0;
			y++;
		}
		x++;
	}
	return (0);
}
