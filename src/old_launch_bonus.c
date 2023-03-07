/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_bonus.c                                     :+:      :+:    :+:   */
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

int	ft_launch(const char *filename)
{
	t_map	map;
	t_game	game;

	ft_init_map(&map);
	map.filename = (char *) filename;
	if (ft_map_isvalid(&map) == 0)
		ft_exit(map.exit_str, -1);
	close(map.fd);
	game.map = &map;
	ft_init_game(&game);
	if (ft_memload_images(&game) == 0)
		ft_exit("ERR_IMGS", 0);
	ft_put_images(&game);
	mlx_hook(game.mlx_window, ON_KEYDOWN, 0, &ft_keycode, &game);
	mlx_hook(game.mlx_window, ON_DESTROY, 0, &ft_destroy, &game);
	mlx_loop_hook(game.mlx, &ft_state_render, &game);
	mlx_loop(game.mlx);
	ft_memunload_images(&game);
	ft_log("> OK");
	return (0);
}

int	ft_launch_bypass(const char *filename)
{
	t_map	map;
	t_game	game;
	
	exit(0);
	ft_init_map(&map);
	map.filename = (char *) filename;
	ft_map_isvalid(&map);
	close(map.fd);
	game.map = &map;
	ft_init_game(&game);
	if (ft_memload_images(&game) == 0)
		ft_exit("ERR_IMGS", 0);
	ft_put_images(&game);
	mlx_hook(game.mlx_window, ON_KEYDOWN, 0, &ft_keycode, &game);
	mlx_hook(game.mlx_window, ON_DESTROY, 0, &ft_destroy, &game);
	mlx_loop_hook(game.mlx, &ft_state_render, &game);
	mlx_loop(game.mlx);
	ft_memunload_images(&game);
	ft_log("> OK (bypass)");
	return (0);
}

int	ft_generate(const char *filename, int x, int y)
{
	int	fd;

	if (x == 0 && y == 0)
	{
		ft_printf("hey\n");
		ft_launch(filename);
	}
	else
	{
		fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
			ft_exit("Could not open/create file", 0);
		ft_write_empty_map(fd, x, y);
		close(fd);
		ft_launch(filename);
	}
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
