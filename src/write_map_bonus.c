/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:55:45 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/03/02 17:55:46 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_write_empty_map(int fd, int x, int y)
{
	int	xx;
	int	yy;

	x += 2;
	y += 2;
	xx = 0;
	while (xx++ < x)
	{
		yy = 0;
		while (yy < y)
		{
			if (yy == 0 || yy == y - 1 || xx == 1 || xx == x)
				write(fd, "1", 1);
			else
				write(fd, "0", 1);
			if (xx == 2 && yy == 0 && y > 4)
				yy += write(fd, "ECP", 3);
			yy++;
		}
		write(fd, "\n", 1);
	}
	ft_putchar_fd(0, fd);
}

void	ft_write_map(t_map *map, int fd)
{
	t_map_item	**arr;
	size_t		x;
	size_t		y;

	fd = open(map->filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
	arr = map->arr;
	x = 0;
	while (x < map->lstsize)
	{
		y = 0;
		while (y < map->lnlen)
		{
			write(fd, &arr[x][y].c, 1);
			y++;
		}
		write(fd, "\n", 1);
		x++;
	}
	ft_printf("Saved map: %s\n", map->filename);
}
