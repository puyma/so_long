/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:22:21 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/24 12:50:37 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int		ft_solve(t_map *map, unsigned x, unsigned y);

// faltara comprovar (ft_solve) des de cadaun dels collectibles al exit

int	ft_path_isvalid(t_map *map)
{
	map->exit_str = ERR_PATH;
	map->player = ft_locate_character(map, C_PLAYER);
	map->exit = ft_locate_character(map, C_EXIT);
	ft_log("Searching for a valid path...");
	if (map->player == NULL || map->exit == NULL)
		return (0);
	if (ft_solve(map, map->player->x, map->player->y) != 0)
		return (1);
	return (0);
}

static int	ft_solve(t_map *map, unsigned x, unsigned y)
{
	if (x == (unsigned)(map->exit->x) && y == (unsigned)(map->exit->y))
	{
		if (LOG_LEVEL > 0)
			ft_printf("> Reached exit: %d, %d\n", x, y);
		return (1);
	}
	if (x >= map->lstsize || y >= map->lnlen)
		return (0);
	if (map->arr[x][y].i == 1)
		return (0);
	map->arr[x][y].i = 1;
	if (LOG_LEVEL > 0)
		ft_printf("> Visited: %u, %u\n", x, y);
	if (ft_solve(map, x, y + 1))
		return (1);
	if (ft_solve(map, x + 1, y))
		return (1);
	if (ft_solve(map, x, y - 1))
		return (1);
	if (ft_solve(map, x - 1, y))
		return (1);
	map->arr[x][y].i = 0;
	return (0);
}
