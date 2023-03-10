/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:18:21 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/03/10 17:48:08 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_check_surround(char *content, int line, int width, int height);
static int	ft_check_allowedchar(char *content);
static int	ft_check_length(t_map *map);

// once everything parsed, determinate if the map is valid for the game

int	ft_check_map(t_map *map)
{
	t_list	*t;
	int		nline;

	t = map->list;
	nline = 0;
	while (t != NULL)
	{
		if (map->width == map->height)
			ft_exit("Map cannot be square", 44);
		if (ft_check_length(map) == 0)
			ft_exit("All lines should have the same amount of characters", 22);
		if (ft_check_allowedchar(t->content) == 0)
			ft_exit("Found some shit inside you map", 32);
		if (!ft_check_surround(t->content, nline, map->width, map->height))
			ft_exit("Invalid map structure: surroundings", 24);
		nline++;
		t = t->next;
	}
	return (1);
}

int	ft_additional_check(t_game *game)
{
	if (game->n_player > 1 || game->n_exit > 1 || game->n_collectible < 1)
		return (0);
	return (1);
}

static int	ft_check_length(t_map *map)
{
	t_list	*t;
	size_t	len;

	t = map->list;
	len = ft_strlen(t->content);
	while (t != NULL)
	{
		if (len != ft_strlen(t->content))
			return (0);
		len = ft_strlen(t->content);
		t = t->next;
	}
	return ((int) len);
}

static int	ft_check_allowedchar(char *content)
{
	char	*line;

	line = content;
	while (*line != '\0')
	{
		if (ft_strchr(C_ALLOWED, *line) == 0)
			return (0);
		line++;
	}
	return (1);
}

static int	ft_check_surround(char *content, int line, int width, int height)
{
	char	*s;

	s = content;
	if (s[0] != C_WALL || s[width - 1] != C_WALL)
		return (0);
	else if (line == 0 || line == height)
	{
		while (*s != '\0')
		{
			if (*s++ != C_WALL)
				return (0);
		}
	}
	return (1);
}
