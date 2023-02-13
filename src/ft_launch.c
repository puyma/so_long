/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:10:16 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/13 13:02:46 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

int	ft_launch(const char *input_file)
{
	t_map	map;

	map.c_wall = WALL;
	map.filename = (char *) input_file;
	if (ft_map_isvalid(&map))
	{
		write(1, "OK\n", 3);
	}
	else
		ft_exit_str(map.exit_str, -1);
	return (0);
}

// if (ft_map_isvalid(&map)) -> write(1, "OK\n", 3); //ft_launch_graphics();
