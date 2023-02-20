/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:02:54 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/20 09:47:31 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int					ft_filext_isvalid(char *filename, char *ext);
static int			ft_load_map(t_map *map);
static int			ft_check_length(t_map *map);
static int			ft_isrectangle(t_map *map);
int					ft_check_characters(t_map *map);
int					ft_check_surroundings(t_map *map);
static t_map_item	**ft_map2array(t_map *map);

int	ft_map_isvalid(t_map *map)
{
	ft_printf("> %s\n", map->filename);
	if (ft_filext_isvalid(map->filename, MAP_EXT) == 0)
		ft_exit_str(ERR_01, 3);
	map->fd = open(map->filename, O_RDONLY);
	if (map->fd == -1)
		ft_exit_str(ERR_FD, 4);
	if (read(map->fd, NULL, 0) != 0)
		ft_exit_str(ERR_FD_RD, 0);
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
	{
		arr[i] = (t_map_item *) ft_calloc((map->lnlen + 1), sizeof(t_map_item));
		i++;
	}
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

/* ==================== */

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
			map->exit_str = ERR_N_LINES;
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

int	ft_path_isvalid(t_map *map)
{
	int			x;
	int			y;
	t_map_item	**arr;

	map->arr = ft_map2array(map);
	map->exit_str = ERR_PATH;
	x = 0;
	y = 0;
	arr = map->arr;
	return (1);
	return (0);
}
