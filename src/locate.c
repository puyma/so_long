/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:28:21 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/03/10 15:54:04 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_list	*ft_locate_items(int **board, int c)
{
	t_list		*list;
	t_vector	*position;
	int			x;
	int			y;

	list = NULL;
	x = 0;
	y = 0;
	position = ft_locate_character(board, x, y, c);
	while (position != NULL)
	{
		ft_lstadd_back(&list, ft_lstnew(position));
		x = position->x;
		y = position->y + 1;
		position = ft_locate_character(board, x, y, c);
	}
	return (list);
}

t_vector	*ft_locate_character(int **board, int x, int y, int c)
{
	t_vector	*coordinate;

	coordinate = (t_vector *) ft_calloc(1, sizeof(t_vector));
	if (coordinate == NULL)
		ft_exit("Could not allocate memory", 10);
	while (board[x] != NULL)
	{
		while (board[x][y] != '\0')
		{
			if (board[x][y] == c)
			{
				coordinate->x = x;
				coordinate->y = y;
				return (coordinate);
			}
			y++;
		}
		y = 0;
		x++;
	}
	free(coordinate);
	return (NULL);
}
