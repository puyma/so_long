/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:10:16 by mpuig-ma          #+#    #+#             */
/*   Updated: 2022/11/07 12:27:34 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

int	ft_launch(const char *input)
{
	int	fd;

	fd = open(input, O_RDONLY);
	if (fd == -1)
	{
		strerror(2);
		return (2);
	}
	//ft_check_map(fd);
	ft_launch_graphics();
	//int		mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey);
	return (0);
}
