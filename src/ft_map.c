/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:02:54 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/01/17 19:30:01 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

static int	ft_filename_isvalid(t_map *map);
static int	ft_path_isvalid(t_map *map);
static int	ft_load_map(t_map *map);

int	ft_map_isvalid(t_map *map)
{
	ft_printf("> %s\n", map->filename);
	if (!ft_filename_isvalid(map))
		ft_exit_str("Filename is not valid", 3);
	map->fd = open(map->filename, O_RDONLY);
	if (map->fd == -1)
		ft_exit_str("Could not open fd", 4);
	if (read(map->fd, NULL, 0) != 0)
		ft_exit_str("Couldn\'t read from file descriptor", 0);
	ft_load_map(map);
	if (ft_content_isvalid(map) && ft_path_isvalid(map))
		return (1);
	else
		ft_exit_str("Invalid map", 5);
	return (0);
}

static int	ft_filename_isvalid(t_map *map)
{
	int	path_length;

	path_length = ft_strlen(map->filename);
	if (path_length == 0 || path_length > FILENAME_LEN)
		return (0);
	if (ft_strncmp((map->filename + path_length - 4), ".ber", 4) != 0)
		return (0);
	return (1);
}

static int	ft_load_map(t_map *map)
{
	char	*line;
	t_list	*temp;

	map->lst = NULL;
	line = get_next_line(map->fd);
	while (line && *line != '1')
	{
		free(line);
		line = get_next_line(map->fd);
	}
	while (line && *line == '1')
	{
		temp = ft_lstnew(line);
		ft_lstadd_back(&map->lst, temp);
		line = get_next_line(map->fd);
	}
	ft_lstiter(map->lst, ft_delete_nl);
	map->lstsize = (unsigned) ft_lstsize(map->lst);
	return (0);
}

static int	ft_path_isvalid(t_map *map)
{
	(void) map;
	return (1);
	return (0);
}
