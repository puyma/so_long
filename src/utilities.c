/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:28:52 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/20 12:45:49 by mpuig-ma         ###   ########.fr       */
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
