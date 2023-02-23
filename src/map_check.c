/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:24:51 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/23 18:37:51 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_check_wall_str(char *temp, int c);
static int	ft_check_allowedchar(t_map *map, char *line);

int	ft_check_length(t_map *map)
{
	t_list	*t;
	size_t	len;

	map->exit_str = ERR_N_LINES;
	t = map->lst;
	len = ft_strlen(t->content);
	while (t != NULL)
	{
		if (len != ft_strlen(t->content))
			return (0);
		len = ft_strlen(t->content);
		t = t->next;
	}
	map->lnlen = len;
	return ((int) len);
}

int	ft_check_characters(t_map *map)
{
	t_list	*t;

	map->exit_str = ERR_CHAR_INV;
	t = map->lst;
	while (t != NULL)
	{
		if (ft_check_allowedchar(map, t->content) == 0)
			return (0);
		t = t->next;
	}
	map->exit_str = ERR_CHAR_TM;
	if (map->n_player > 1 || map->n_exit > 1 || map->n_collectible < 1)
		return (0);
	return (1);
}

static int	ft_check_allowedchar(t_map *map, char *line)
{
	while (*line != '\0')
	{
		if (ft_strchr(C_ALLOWED, *line) == 0)
			return (0);
		if (*line == C_COLLECTIBLE)
			map->n_collectible++;
		else if (*line == C_EXIT)
			map->n_exit++;
		else if (*line == C_PLAYER)
			map->n_player++;
		line++;
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
		if (temp[0] != C_WALL || temp[map->lnlen - 1] != C_WALL)
			return (0);
		else if ((line == 0 || line == map->lstsize)
			&& ft_check_wall_str(temp, C_WALL) != 0)
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
