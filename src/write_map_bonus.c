/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:55:45 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/03/02 17:55:46 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_write_empty_map(int fd, int y, int x)
{
	int	xx;
	int	yy;

	x += 2;
	y += 2;
	xx = 0;
	while (xx++ < x)
	{
		yy = 0;
		while (yy++ < y)
		{
			write(fd, "1", 1);
			if (xx == 2 && yy == 1)
				yy += write(fd, "ECP", 3);
		}
		write(fd, "\n", 1);
	}
	ft_putchar_fd(0, fd);
	return (0);
}

void	ft_write_map(t_map *map, int fd)
{
	t_map_item	**arr;
	size_t		x;
	size_t		y;

	fd = open(map->filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
	arr = map->arr;
	y = 0;
	while (y < map->lnlen)
	{
		x = 0;
		while (x < map->lstsize)
		{
			write(fd, &arr[x][y].c, 1);
			x++;
		}
		write(fd, "\n", 1);
		y++;
	}
}
