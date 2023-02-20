/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:10:16 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/20 11:30:46 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_init_map(t_map *map);
static void	ft_init_game(t_game *game);
void		*ft_new_window(t_game *game, char *title);

int	ft_launch(const char *input_file)
{
	t_map	map;

	ft_init_map(&map);
	map.filename = (char *) input_file;
	if (ft_map_isvalid(&map))
	{
		write(1, "> OK\n", 5);
		ft_launch_graphics(&map);
	}
	else
		ft_exit_str(map.exit_str, -1);
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
	map->c_floor = C_EMPTY_SPACE;
	map->c_wall = C_WALL;
	map->c_collectible = C_COLLECTIBLE;
	map->c_exit = C_EXIT;
	map->c_player = C_PLAYER;
}

static void	ft_init_game(t_game *game)
{
	game->size = PIX_SIZE;
	game->width = game->map->lnlen * game->size;
	game->height = game->map->lstsize * game->size;
	game->state = Running;
	game->n_moves = 0;
	game->mlx = mlx_init();
	game->mlx_window = ft_new_window(game, "so_long");
	game->state = Running;
	ft_log_state(game);
}

void	*ft_new_window(t_game *game, char *title)
{
	void	*window;

	window = NULL;
	window = mlx_new_window(game->mlx, game->width, game->height, title);
	return (window);
}
