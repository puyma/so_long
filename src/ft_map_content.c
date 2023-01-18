/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_content.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:22:14 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/01/18 18:37:25 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

int	ft_check_characters(t_map *map);
int	ft_check_surroundings(t_map *map);

int	ft_check_characters(t_map *map)
{
	t_list	*t;

	t = map->lst;
	while (t != NULL)
	{
		if (ft_strchr(t->content, EMPTY_SPACE) == 0
			|| ft_strchr(t->content, WALL) == 0
			|| ft_strchr(t->content, MAP_EXIT) == 0
			|| ft_strchr(t->content, COLLECTIBLE) == 0
			|| ft_strchr(t->content, PLAYER) == 0)
		{
			map->exit_str = ERR_CHAR;
			return (0);
		}
		t = t->next;
	}
	return (1);
}

int	ft_check_surroundings(t_map *map)
{
	(void) map;
	return (1);
}
