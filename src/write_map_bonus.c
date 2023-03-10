/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:33:45 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/03/10 17:55:04 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// exits to manage here (return edit)

int	ft_write_empty_map(char *filename, int x, int y)
{
	if (x < 1 || y < 1)
	{
		ft_printf("usage: ./bonus file\n");
		exit(0);
	}
	(void) filename;
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
