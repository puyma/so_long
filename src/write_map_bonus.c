/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:33:45 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/03/11 19:22:52 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// exits to manage here (return edit)

// this function should generate an empty int **board 
// and pass it to ft_write_map();

static int	ft_fill_map(int **board, int x, int y);

int	ft_generate_map(char *filename, int x, int y)
{
	int	**board;

	if (x < 1 || y < 1)
	{
		ft_printf("usage: ./generator file [width > 0] [height > 0]\n");
		exit(0);
	}
	x += 2;
	y += 2;
	board = ft_new_board(x, y);
	ft_fill_map(board, x, y);
	ft_write_map(filename, board);
	return (0);
}

	/*
	ft_unload_board(board);
	if (board)
		free(board);
	*/

static int	ft_fill_map(int **board, int x, int y)
{
	int	xx;
	int	yy;

	xx = 0;
	while (xx < x)
	{
		yy = 0;
		while (yy < y)
		{
			ft_printf("%d, %d - %d, %d\n", x, y, xx, yy);
			if (yy == 0 || yy == y - 1 || xx == 0 || xx == x - 1)
				board[yy][xx] = '1';
			else
				board[yy][xx] = '0';
			yy++;
		}
		xx++;
	}
	return (0);
}

//if (xx == 2 && yy == 0 && y > 4)
//	yy += write(fd, "ECP", 3);

void	ft_write_map(char *filename, int **board)
{
	size_t		x;
	size_t		y;
	int			fd;

	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
	fd = 1;
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
	ft_putchar_fd(0, fd);
	ft_printf("Saved map: %s\n", filename);
}
