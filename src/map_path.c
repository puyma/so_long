/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:21:42 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/14 16:55:59 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * enum 
 *  If dir=0 try Up direction.
 *  If dir=1 try left direction.
 *  If dir=2 try down direction.
 *  If dir=3 try right direction.
 */

static t_map_item	**ft_map2array(t_map *map);

static t_map_item	**ft_map2array(t_map *map)
{
	t_list			*t;
	unsigned int	i;
	unsigned int	line;
	t_map_item		**arr;
	char			*temp;

	t = map->lst;
	i = 0;
	line = 0;
	arr = (t_map_item **) ft_calloc((map->lstsize + 1), sizeof(t_map_item *));
	if (arr == NULL)
		return (NULL);
	while (i < map->lstsize)
		arr[i++] = (t_map_item *) ft_calloc((map->lnlen + 1), sizeof(t_map_item));
	i = 0;
	line = 0;
	while (t != NULL && line < map->lstsize)
	{
		temp = t->content;
		i = 0;
		while (i < map->lnlen)
		{
			arr[line][i].c = temp[i];
			i++;
		}
		line++;
		t = t->next;
	}
	return (arr);
}

int	ft_path_isvalid(t_map *map)
{
	int		x;
	int		y;
	t_map_item	**arr;

	map->arr = ft_map2array(map);
	map->exit_str = "Path is invalid";
	x = 0;
	y = 0;
	arr = map->arr;
	return (1);
	return (0);
}
