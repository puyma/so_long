/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:13:21 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/24 14:01:59 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define ON_BUTTONPRESS	4

static int	ft_empty_map(t_map *map, int x, int y);
static int	ft_set_generator_events(t_game *generator);
static int 	ft_click(t_game *generator);

int	main(int argc, char **argv)
{
	t_game	generator;

	if (argc != 3)
		return (0);
	ft_empty_map(generator.map, ft_atoi(argv[2]), ft_atoi(argv[1]));
	generator.width = ft_atoi(argv[1]);
	generator.height = ft_atoi(argv[2]);
	generator.size = PIX_SIZE;
	generator.state = Running;
	generator.mlx = mlx_init();
	generator.mlx_window = ft_new_window(&generator, "map generator");
	ft_set_generator_events(&generator);
	generator.i_wall = ft_memload_img(&generator, WALL);
	ft_fill_window(&generator, generator.i_wall);
	mlx_loop(generator.mlx);
	return (0);
}

static int	ft_empty_map(t_map *map, int x, int y)
{
	t_map_item		**arr;
	unsigned int	i;

	map->lstsize = x;
	map->lnlen = y;
	i = 0;
	arr = (t_map_item **) ft_calloc((map->lstsize + 1), sizeof(t_map_item *));
	while (arr && i < map->lstsize)
	{
		arr[i] = (t_map_item *) ft_calloc((map->lnlen + 1), sizeof(t_map_item));
		i++;
	}
	map->arr = arr;
	return (0);
}

static int	ft_set_generator_events(t_game *generator)
{
	mlx_hook(generator->mlx_window, ON_KEYDOWN, 0, &ft_click, generator);
	return (0);
}

static int 	ft_click(t_game *generator)
{
	(void) generator;
	write(1, "Click\n", 6);
	return (0);
}
