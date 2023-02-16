/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:10:16 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/16 11:36:11 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_init_map(t_map *map);

int	ft_launch(const char *input_file)
{
	t_map	map;

	ft_init_map(&map);
	map.filename = (char *) input_file;
	if (ft_map_isvalid(&map))
	{
		write(1, "> OK\n", 5);
		ft_launch_graphics(&map);
	}
	else
		ft_exit_str(map.exit_str, -1);
	return (0);
}

static int	ft_init_map(t_map *map)
{
	map->c_floor = C_EMPTY_SPACE;
	map->c_wall = C_WALL;
	map->c_collectible = C_COLLECTIBLE;
	map->c_exit = C_EXIT;
	map->c_player = C_PLAYER;
	return (0);
}
