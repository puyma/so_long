/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_content.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:22:14 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/01/18 17:22:36 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

static int	ft_check_length(t_map *map);
static int	ft_isrectangle(t_map *map);
static int	ft_check_characters(t_map *map);
static int	ft_check_surroundings(t_map *map);

int	ft_content_isvalid(t_map *map)
{
	if (!ft_check_length(map) || !ft_isrectangle(map))
		return (0);
	if (!ft_check_characters(map))
		return (0);
	if (!ft_check_surroundings(map))
		return (0);
	return (1);
}

static int	ft_check_length(t_map *map)
{
	t_list	*t;
	size_t	len;

	t = map->lst;
	len = ft_strlen(t->content);
	while (t != NULL)
	{
		if (len != ft_strlen(t->content))
		{
			map->exit_str = "Lines should contain the same number of chars";
			return (0);
		}
		len = ft_strlen(t->content);
		t = t->next;
	}
	return (1);
}

static int	ft_isrectangle(t_map *map)
{
	size_t	len;

	len = ft_strlen((map->lst)->content);
	if (len == map->lstsize)
	{
		map->exit_str = "Map is not rectangular";
		return (0);
	}
	return (1);
}

static int	ft_check_characters(t_map *map)
{
	t_list	*t;

	t = map->lst;
	while (t != NULL)
	{
		if (ft_strchr(t->content, EMPTY_SPACE) == 0
			|| ft_strchr(t->content, WALL) == 0
			|| ft_strchr(t->content, MAP_EXIT) == 0
			|| ft_strchr(t->content, COLLECTIBLE) == 0
			|| ft_strchr(t->content, 'P') == 0)
		{
			map->exit_str = "Found some shit inside your fmap";
			return (0);
		}
		t = t->next;
	}
	return (1);
}

static int	ft_check_surroundings(t_map *map)
{
	(void) map;
	return (1);
}
