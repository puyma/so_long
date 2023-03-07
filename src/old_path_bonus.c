/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:22:21 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/24 12:50:37 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// faltara comprovar (ft_solve) des de cadaun dels collectibles al exit

static int	ft_solve(t_map *map, unsigned x, unsigned y);
static int	ft_clear_path(t_map *map);

int	ft_path_isvalid(t_map *map)
{
	t_list		*collectibles;
	t_vector	*collectible;

	collectibles = map->collectibles;
	map->exit_str = ERR_PATH;
	map->player = ft_locate_character(map, C_PLAYER);
	map->exit = ft_locate_character(map, C_EXIT);
	ft_log("Searching for a valid path...");
	if (map->player == NULL || map->exit == NULL)
		return (0);
	if (ft_solve(map, map->player->x, map->player->y) == 0)
		return (0);
	while (collectibles != NULL)
	{
		if (LOG_LEVEL > 0)
			ft_printf("collectible: %u %u\n");
		collectible = collectibles->content;
		ft_clear_path(map);
		if (ft_solve(map, collectible->x, collectible->y) == 0)
			return (0);
		collectibles = collectibles->next;
	}
	return (1);
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

int	ft_clear_path(t_map *map)
{
	unsigned int	x;
	unsigned int	y;

	x = 0;
	y = 0;
	while (map->arr[x] != NULL)
	{
		y = 0;
		while (map->arr[x][y].c != '\0')
		{
			if (map->arr[x][y].c == C_WALL)
				map->arr[x][y].i = 1;
			else
				map->arr[x][y].i = 0;
			y++;
		}
		x++;
	}
	return (0);
}
