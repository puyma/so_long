/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:23:29 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/22 11:23:31 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	ft_exit(char *error_str, int error_num)
{
	if (*error_str == '\0')
		error_str = strerror(error_num);
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(error_str, 1);
	ft_putstr_fd(" [", 1);
	ft_putnbr_fd(error_num, 1);
	ft_putstr_fd("]", 1);
	ft_putchar_fd('\n', 1);
	exit(error_num);
}

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

t_vector	*ft_locate_character(t_map *map, int c)
{
	t_vector	*coordinates;
	int			x;
	int			y;

	coordinates = ft_calloc(1, sizeof(t_vector));
	x = 0;
	while (coordinates && map->arr[x] != NULL)
	{
		y = 0;
		while (map->arr[x][y].c != '\0')
		{
			if (map->arr[x][y].c == c)
			{
				coordinates->x = x;
				coordinates->y = y;
				return (coordinates);
			}
			y++;
		}
		x++;
	}
	return (NULL);
}

int	ft_ismovekey(int keycode)
{
	enum e_character	direction;

	direction = None;
	if (keycode == KEY_UP || keycode == KEY_W)
		direction = Up;
	else if (keycode == KEY_DOWN || keycode == KEY_S)
		direction = Down;
	else if (keycode == KEY_RIGHT || keycode == KEY_D)
		direction = Right;
	else if (keycode == KEY_LEFT || keycode == KEY_A)
		direction = Left;
	return (direction);
}
