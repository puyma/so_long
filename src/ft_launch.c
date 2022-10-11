/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:10:16 by mpuig-ma          #+#    #+#             */
/*   Updated: 2022/10/11 17:26:17 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

#define WIDTH 1080
#define HEIGHT 720

int	ft_launch_game(void)
{
	void	*mlx;
	void	*mlx_window;

	mlx = mlx_init();
	mlx_window = mlx_new_window(mlx, WIDTH, HEIGHT, "TDB");
	mlx_loop(mlx);
	return (0);
}

int	ft_launch(const char *input)
{
	int	fd;

	fd = open(input, O_RDONLY);
	if (fd == -1)
	{
		strerror(2);
		return (2);
	}
	ft_check_map(fd);
	ft_launch_game();
	write(1, "We are all in this together!\n", 30);
	return (0);
}
