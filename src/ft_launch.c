/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:10:16 by mpuig-ma          #+#    #+#             */
/*   Updated: 2022/11/15 16:56:59 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

int	ft_launch(const char *input)
{
	t_map	map;
	
	if (ft_check_map(input, &map) == 0)
		ft_launch_graphics();
	return (0);
}
