/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:38:27 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/03/10 15:40:23 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_map2array(t_map *map);

int	**ft_new_board(size_t x, size_t y)
{
	int		**board;
	size_t	i;

	board = (int **) ft_calloc(y + 1, sizeof(int *));
	if (board == NULL)
		ft_exit("Could not allocate memory", 14);
	i = 0;
	while (i < y)
		board[i++] = (int *) ft_calloc(x + 1, sizeof(int));
	return (board);
}

int	ft_load_board(t_map *map)
{
	map->board = ft_new_board(map->width, map->height);
	ft_map2array(map);
	return (0);
}

static void	ft_map2array(t_map *map)
{
	t_list	*list;
	int		line;
	size_t	i;
	char	*temp;

	list = map->list;
	line = 0;
	i = 0;
	while (list != NULL)
	{
		i = 0;
		while (i < map->width)
		{
			temp = list->content;
			map->board[line][i] = temp[i];
			i++;
		}
		line++;
		list = list->next;
	}
}

void	ft_unload_board(int **board)
{
	int	x;

	x = 0;
	while (board[x] != NULL)
		free(board[x++]);
	free(board);
}
