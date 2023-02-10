/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_content.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:22:14 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/10 14:05:54 by mpuig-ma         ###   ########.fr       */
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
			if (ft_strchr(ALLOWED_CHARS, *temp) != 0)
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
	(void) map;
	return (1);
}
