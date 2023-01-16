/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:27:35 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/01/16 16:32:03 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

static int	ft_filename_isvalid(t_map *map);
static int	ft_content_isvalid(t_map *map);
static int	ft_path_isvalid(t_map *map);

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
	if (ft_content_isvalid(map) && ft_path_isvalid(map))
		return (1);
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

static int	ft_content_isvalid(t_map *map)
{
	(void) map;
	return (1);
	return (0);
}

static int	ft_path_isvalid(t_map *map)
{
	(void) map;
	return (1);
	return (0);
}
