/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_content.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:22:14 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/13 15:09:29 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

int	ft_check_characters(t_map *map);
int	ft_check_surroundings(t_map *map);

int	ft_check_characters(t_map *map)
{
	t_list	*t;
	char	*temp;
	size_t	i;

	t = map->lst;
	temp = NULL;
	while (t != NULL)
	{
		i = map->lnlen;
		temp = t->content;
		while (i-- > 0)
		{
			if (ft_strchr(ALLOWED_CHARS, *temp) == 0)
			{
				map->exit_str = "Invalid character found in map.";
				return (0);
			}
			temp++;
		}
		t = t->next;
	}
	return (1);
}

int	ft_check_surroundings(t_map *map)
{
	t_list			*t;
	char			*temp;
	unsigned int	line;
	unsigned int	i;

	t = map->lst;
	temp = NULL;
	line = 0;
	while (t != NULL)
	{
		temp = t->content;
		if (line == 0 || line == map->lstsize)
		{
			i = 0;
			while (i < map->lnlen)
			{
				if (temp[i] != map->c_wall)
				{
					map->exit_str = "Map is not surrounded by walls";
					return (0);
				}
				i++;
			}
		}
		else if (temp[0] != map->c_wall || temp[map->lnlen - 1] != map->c_wall)
		{
			map->exit_str = "Map is not surrounded by walls";
			return (0);
		}
		line++;
		t = t->next;
	}
	return (1);
}
