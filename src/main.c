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

int	main(int argc, char **argv)
{
	int		fd;
	int		x;
	int		y;
	char	*filename;

	if (argc != 4)
		ft_exit("Arguments should be: filename, width > 0, height > 0", 0);
	x = ft_atoi(argv[2]);
	y = ft_atoi(argv[3]);
	if (x <= 0 || y <= 0 || x == y)
		ft_exit("Arguments should be: filename, width > 0, height > 0", 0);
	if (ft_extension_isvalid(argv[1], MAP_EXT) == 0)
		filename = ft_strjoin(argv[1], MAP_EXT);
	else
		filename = argv[1];
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		ft_exit("Could not open/create file", 0);
	ft_write_empty_map(fd, x, y);
	close(fd);
	ft_launch(filename);
	return (0);
}

#endif
