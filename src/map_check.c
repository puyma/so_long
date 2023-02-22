/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:24:51 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/22 11:24:55 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_check_wall_str(char *temp, int c);

int	ft_check_length(t_map *map)
{
	t_list	*t;
	size_t	len;

	t = map->lst;
	len = ft_strlen(t->content);
	while (t != NULL)
	{
		if (len != ft_strlen(t->content))
		{
			map->exit_str = ERR_N_LINES;
			return (0);
		}
		len = ft_strlen(t->content);
		t = t->next;
	}
	map->lnlen = len;
	return ((int) len);
}

int	ft_isrectangle(t_map *map)
{
	size_t	len;

	len = ft_strlen((map->lst)->content);
	if (len == map->lstsize)
	{
		map->exit_str = ERR_RECT;
		return (0);
	}
	return ((int) len);
}

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
			if (ft_strchr(C_ALLOWED, *temp) == 0)
			{
				map->exit_str = ERR_CHAR_2;
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

	t = map->lst;
	temp = NULL;
	line = 0;
	map->exit_str = ERR_SURR;
	while (t != NULL)
	{
		temp = t->content;
		if (temp[0] != map-> c_wall || temp[map->lnlen - 1] != map->c_wall)
			return (0);
		else if ((line == 0 || line == map->lstsize)
			&& ft_check_wall_str(temp, map->c_wall) != 0)
			return (0);
		line++;
		t = t->next;
	}
	return (1);
}

static int	ft_check_wall_str(char *temp, int c)
{
	while (*temp != '\0')
	{
		if (*temp != c)
			return (1);
		temp++;
	}
	return (0);
}
