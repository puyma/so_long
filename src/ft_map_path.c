/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:21:42 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/13 18:59:03 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

/*
 * eenum 
 *     If dir=0 try Up direction.
    If dir=1 try left direction.
    If dir=2 try down direction.
    If dir=3 try right direction.
*/

int	ft_path_isvalid(t_map *map)
{
	map->exit_str = "Path is invalid";
	return (1);
	return (0);
}
