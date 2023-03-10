/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:33:45 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/03/11 00:42:12 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// exits to manage here (return edit)

// this function should generate an empty int **board 
// and pass it to ft_write_map();

int	ft_write_empty_map(char *filename, int x, int y)
{
	const int	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0666);

	if (x < 1 || y < 1)
	{
		ft_printf("usage ./generator file [width > 0] [height > 0]\n");
		exit(0);
	}
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
	return (0);
}

void	ft_write_map(char *filename, int **board)
{
	size_t		x;
	size_t		y;
	int			fd;

	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
	x = 0;
	y = 0;
	while (board[x] != NULL)
	{
		y = 0;
		while (board[x][y] != '\0')
		{
			write(fd, &board[x][y], 1);
			y++;
		}
		write(fd, "\n", 1);
		x++;
	}
	ft_printf("Saved map: %s\n", filename);
}
