/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:36:50 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/14 16:56:32 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#ifndef GENERATOR

int	main(int argc, char **argv)
{
	const char	*default_map = "maps/default.ber";

	if (argc == 1)
		ft_launch(default_map);
	else if (argc == 2)
		ft_launch(argv[1]);
	else if (argc > 2)
		ft_exit(NULL, 22);
	return (0);
}

#else

static int	ft_write_empty_map(int fd, int x, int y);

int	main(int argc, char **argv)
{
	int	fd;
	int	x;
	int	y;
	
	if (argc != 4)
		ft_exit("Arguments should be: filename, width > 0, height > 0", 0);
	x = ft_atoi(argv[2]);
	y = ft_atoi(argv[3]);
	if (x == 0 || y == 0)
		ft_exit("Arguments should be: filename, width > 0, height > 0", 0);
	fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC);
	if (fd == -1)
		ft_exit("Could not open/create file", 0);
	ft_write_empty_map(fd, x, y);
	close(fd);
	return (0);
}

static int	ft_write_empty_map(int fd, int y, int x)
{
	int	xx;
	int	yy;
	
	xx = 0;
	while (xx < x)
	{
		yy = 0;
		while (yy < y)
		{
			write(fd, "1", 1);
			yy++;
		}
		write(fd, "\n", 1);
		xx++;
	}
	return (0);
}

#endif