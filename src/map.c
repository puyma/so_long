/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:02:54 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/16 12:19:32 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int			ft_filext_isvalid(char *filename, char *ext);
static int	ft_load_map(t_map *map);
static int	ft_check_length(t_map *map);
static int	ft_isrectangle(t_map *map);

int	ft_map_isvalid(t_map *map)
{
	ft_printf("> %s\n", map->filename);
	if (ft_filext_isvalid(map->filename, MAP_EXT) == 0)
		ft_exit_str(ERR_01, 3);
	map->fd = open(map->filename, O_RDONLY);
	if (map->fd == -1)
		ft_exit_str("Could not open fd", 4);
	if (read(map->fd, NULL, 0) != 0)
		ft_exit_str("Couldn\'t read from file descriptor", 0);
	ft_load_map(map);
	if (ft_check_length(map) == 0 || ft_isrectangle(map) == 0)
		return (0);
	if (ft_check_characters(map) == 0 || ft_check_surroundings(map) == 0)
		return (0);
	if (ft_path_isvalid(map) == 0)
		return (0);
	return (map->lnlen);
}

static int	ft_load_map(t_map *map)
{
	char	*line;
	t_list	*temp;

	map->lst = NULL;
	map->exit_str = ERR_00;
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

int	ft_filext_isvalid(char *filename, char *ext)
{
	size_t	path_length;
	size_t	ext_len;

	path_length = ft_strlen(filename);
	ext_len = ft_strlen(ext);
	if (path_length == 0 || path_length > FILENAME_LEN)
		return (0);
	if (ft_strncmp((filename + path_length - ext_len), ext, ext_len) != 0)
		return (0);
	return ((int) path_length);
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
	map->lnlen = len;
	return ((int) len);
}

static int	ft_isrectangle(t_map *map)
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
