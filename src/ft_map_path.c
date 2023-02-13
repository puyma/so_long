/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:21:42 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/13 16:08:50 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

int	ft_path_isvalid(t_map *map)
{
	ft_printf("> checking path...\n");
	(void) map;
	map->exit_str = "Path is invalid";
	return (0);
}
