/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_locate_character.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:43:50 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/28 13:43:52 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_vector	*ft_locate_character(t_map *map, int c)
{
	t_vector	*coordinates;
	int			x;
	int			y;

	coordinates = ft_calloc(1, sizeof(t_vector));
	x = 0;
	while (coordinates && map->arr[x] != NULL)
	{
		y = 0;
		while (map->arr[x][y].c != '\0')
		{
			if (map->arr[x][y].c == c)
			{
				coordinates->x = x;
				coordinates->y = y;
				return (coordinates);
			}
			y++;
		}
		x++;
	}
	return (NULL);
}
