/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:06:51 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/03/10 18:06:00 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_map	*map;
	t_game	*game;

	if (argc != 1 && argc != 2)
	{
		ft_printf("usage: ./so_long file\n");
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
