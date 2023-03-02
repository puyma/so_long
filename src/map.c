/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:02:54 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/24 12:49:12 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int			ft_path_isvalid(t_map *map);
static t_map_item	**ft_allocate_map(t_map *map);

int	ft_map_isvalid(t_map *map)
{
	ft_log(map->filename);
	if (ft_extension_isvalid(map->filename, MAP_EXT) == 0)
		ft_exit(ERR_01, 3);
	map->fd = open(map->filename, O_RDONLY);
	if (map->fd == -1)
		ft_exit(ERR_FD, 4);
	if (read(map->fd, NULL, 0) != 0)
		ft_exit(ERR_FD_RD, 0);
	if (ft_load_map(map) != 0)
		ft_exit(ERR_02, 6);
	if (ft_check_length(map) == 0 || map->lstsize == map->lnlen)
		return (0);
	if (ft_check_characters(map) == 0 || ft_check_surroundings(map) == 0)
		return (0);
	map->arr = ft_map2array(map);
	ft_lstclear(&map->lst, &free);
	ft_log("Freed map->lst");
	if (ft_path_isvalid(map) == 0)
		return (0);
	return (map->lnlen);
}

static int	ft_path_isvalid(t_map *map)
{
	map->exit_str = ERR_PATH;
	map->player = ft_locate_character(map, C_PLAYER);
	map->exit = ft_locate_character(map, C_EXIT);
	ft_log("Searching for a valid path...");
	if (map->player == NULL || map->exit == NULL)
		return (0);
	if (ft_solve(map, map->player->x, map->player->y) != 0)
		return (1);
	return (0);
}

int	ft_load_map(t_map *map)
{
	char	*line;
	t_list	*temp;

	map->lst = NULL;
	map->exit_str = ERR_00;
	line = get_next_line(map->fd);
	if (line == NULL)
		return (1);
	while (line && *line != C_WALL)
	{
		free(line);
		line = get_next_line(map->fd);
	}
	while (line && *line == C_WALL)
	{
		temp = ft_lstnew(line);
		ft_lstadd_back(&map->lst, temp);
		line = get_next_line(map->fd);
	}
	ft_lstiter(map->lst, ft_delete_nl);
	map->lstsize = (unsigned) ft_lstsize(map->lst);
	return (0);
}

t_map_item	**ft_map2array(t_map *map)
{
	t_list			*t;
	unsigned int	i;
	unsigned int	line;
	t_map_item		**arr;
	char			*temp;

	t = map->lst;
	arr = ft_allocate_map(map);
	i = 0;
	line = 0;
	while (arr && t != NULL && line < map->lstsize)
	{
		temp = t->content;
		i = 0;
		while (i < map->lnlen)
		{
			arr[line][i].c = temp[i];
			if (arr[line][i].c == C_WALL)
				arr[line][i].i = 1;
			i++;
		}
		line++;
		t = t->next;
	}
	return (arr);
}

static t_map_item	**ft_allocate_map(t_map *map)
{
	t_map_item		**arr;
	unsigned int	i;

	i = 0;
	arr = (t_map_item **) ft_calloc((map->lstsize + 1), sizeof(t_map_item *));
	while (arr && i < map->lstsize)
	{
		arr[i] = (t_map_item *) ft_calloc((map->lnlen + 1), sizeof(t_map_item));
		i++;
	}
	return (arr);
}
