/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:28:52 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/24 09:18:07 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_delete_nl(void *ptr)
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

void	*ft_new_window(t_game *game, char *title)
{
	void	*window;

	window = NULL;
	window = mlx_new_window(game->mlx, game->width, game->height, title);
	return (window);
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

int	ft_isrectangle(t_map *map)
{
	size_t	len;

	map->exit_str = ERR_RECT;
	len = ft_strlen((map->lst)->content);
	if (len == map->lstsize)
		return (0);
	return ((int) len);
}

int	ft_fill_window(t_game *game, t_imgdata *img)
{
	int			x;
	int			y;
	t_map_item	**arr;

	x = 0;
	y = 0;
	arr = game->map->arr;
	while (arr[x] != NULL)
	{
		y = 0;
		while (arr[x][y].c != '\0')
			ft_put_img(game, img, x, y++);
		x++;
	}
	return (0);
}
