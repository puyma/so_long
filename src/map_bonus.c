/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:37:47 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/03/10 17:51:53 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void		ft_delete_nl(void *ptr);
static size_t	ft_get_largest_ln(t_list *list);

// exits to manage here

t_map	*ft_new_map(char *filename)
{
	t_map	*map;

	map = ft_calloc(sizeof(t_map), 1);
	if (map == NULL)
		ft_exit("Could not allocate memory", 0);
	map->filename = filename;
	map->width = 0;
	map->height = 0;
	map->list = NULL;
	map->board = NULL;
	return (map);
}

// exits to manage here

int	ft_load_map(t_map *map)
{
	char	*line;
	int		fd;

	map->list = NULL;
	if (ft_extension_isvalid(map->filename, MAP_EXT) == 0)
		ft_exit("File extension is not valid", 2);
	fd = open(map->filename, O_RDONLY);
	if (fd == -1 || read(fd, NULL, 0) != 0)
		ft_exit("File does not exist", 2);
	line = get_next_line(fd);
	if (line == NULL || *line == '\0')
		ft_exit("Your ber is empty, I guess", 16);
	while (line != NULL)
	{
		if (*line != '#' && !ft_isspace(*line))
			ft_lstadd_back(&map->list, ft_lstnew(line));
		else
			free(line);
		line = get_next_line(fd);
	}
	ft_lstiter(map->list, &ft_delete_nl);
	map->height = ft_lstsize(map->list);
	map->width = ft_get_largest_ln(map->list);
	close(fd);
	return (0);
}

int	ft_extension_isvalid(char *filename, char *ext)
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

static void	ft_delete_nl(void *ptr)
{
	char	*str;

	str = (char *) ptr;
	while (*str != '\0')
	{
		if (*str == '\n')
			*str = '\0';
		str++;
	}
}

static size_t	ft_get_largest_ln(t_list *list)
{
	size_t	len;
	t_list	*l;

	len = 0;
	l = list;
	while (l != NULL)
	{
		if (len < ft_strlen(l->content))
			len = ft_strlen(l->content);
		l = l->next;
	}
	return (len);
}
