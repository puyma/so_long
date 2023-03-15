/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:08:27 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/03/13 13:28:28 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#ifdef GENERATOR

// better if ft_generate_empty_map (array). so it can be random as well
// if GENERATOR, do not check map, just launch

int	main(int argc, char **argv)
{
	t_map	*map;
	t_game	*game;

	if (argc != 2 && argc != 4)
	{
		ft_printf("usage ./generator file [width > 0] [height > 0]\n");
		return (0);
	}
	if (ft_extension_isvalid(argv[1], MAP_EXT) == 0)
		map = ft_new_map(ft_strjoin(argv[1], MAP_EXT));
	else
		map = ft_new_map(argv[1]);
	if (argc == 4)
		ft_generate_map(map->filename, ft_atoi(argv[3]), ft_atoi(argv[2]));
	ft_load_map(map);
	ft_load_board(map);
	ft_lstclear(&map->list, &free);
	game = ft_new_game(map);
	ft_load_game(game);
	ft_launch(game);
	ft_write_map(map->filename, map->board);
	free(map);
	return (0);
}

#else /* ifndef GENERATOR */

int	main(int argc, char **argv)
{
	t_map	*map;
	t_game	*game;

	if (argc != 1 && argc != 2)
	{
		ft_printf("usage: ./bonus file\n");
		return (0);
	}
	if (argc == 1)
		map = ft_new_map("maps/default.ber");
	else
		map = ft_new_map(argv[1]);
	ft_load_map(map);
	ft_check_map(map);
	ft_load_board(map);
	ft_lstclear(&map->list, &free);
	game = ft_new_game(map);
	ft_load_game(game);
	ft_additional_check(game);
	ft_launch(game);
	free(map);
	return (0);
}

#endif
