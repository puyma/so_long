/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:10:16 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/24 13:32:36 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_init_map(t_map *map);
static void	ft_init_game(t_game *game);

int	ft_launch(const char *input_file)
{
	t_map	map;

	ft_init_map(&map);
	map.filename = (char *) input_file;
	if (ft_map_isvalid(&map))
		ft_launch_graphics(&map);
	else
		ft_exit_str(map.exit_str, -1);
	ft_log("> OK\n");
	return (0);
}

int	ft_launch_graphics(t_map *map)
{
	t_game		game;

	game.map = map;
	ft_init_game(&game);
	if (ft_memload_images(&game) != 0)
		ft_put_images(&game);
	ft_set_events(&game);
	mlx_loop(game.mlx);
	free(game.map);
	return (0);
}

static void	ft_init_map(t_map *map)
{
	map->n_player = 0;
	map->n_exit = 0;
	map->n_collectible = 0;
}

static void	ft_init_game(t_game *game)
{
	game->size = PIX_SIZE;
	game->width = game->map->lnlen * game->size;
	game->height = game->map->lstsize * game->size;
	game->n_moves = 0;
	game->mlx = mlx_init();
	game->mlx_window = ft_new_window(game, "so_long");
	game->state = Running;
	ft_log_state(game->state);
}
