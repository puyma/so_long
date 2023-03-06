/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:36:50 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/14 16:56:32 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#ifdef GENERATOR

int	ft_generate(const char *filename, int x, int y);

int	main(int argc, char **argv)
{
	int		x;
	int		y;
	char	*filename;

	x = 0;
	y = 0;
	if (argc != 4 && argc != 2)
		ft_exit("Usage: filename and/or width > 0, height > 0", 0);
	if (ft_extension_isvalid(argv[1], MAP_EXT) == 0)
		filename = ft_strjoin(argv[1], MAP_EXT);
	else
		filename = argv[1];
	if (argc == 4)
	{
		x = ft_atoi(argv[3]);
		y = ft_atoi(argv[2]);
		if (x <= 0 || y <= 0)
			ft_exit("Usage: filename, width > 0, height > 0", 0);
		else if (x == y)
			ft_exit("Usage: filename, width, height (!= width)", 0);
	}
	ft_printf("receiving: %d, %d\n", x, y);
	ft_generate(filename, x, y);
	return (0);
}

#else

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

#endif