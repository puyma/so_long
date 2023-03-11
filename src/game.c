/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:40:39 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/03/11 23:03:33 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_vector	*ft_isghost_player(t_vector *player);

// ft_put_images -> should only put images, should not do other stuff!

t_game	*ft_new_game(t_map *map)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (game == NULL)
		ft_exit("Could not allocate memory", 4);
	game->size = PIX_SIZE;
	game->width = map->width * game->size;
	game->height = map->height * game->size;
	game->board = map->board;
	game->collectibles = NULL;
	game->exit = NULL;
	game->player = NULL;
	game->n_moves = 0;
	game->n_collectible = 0;
	game->n_exit = 0;
	game->n_player = 0;
	game->filename = map->filename;
	game->mlx = mlx_init();
	game->mlx_window = ft_new_window(game, "so_long");
	game->map = map;
	return (game);
}

// add a player if NULL...maybe also with exit and collectibles?
// cleaning list make the player (and other characters) to not be found properly
// as they are erased... so, removed:
// if (list)
// 	ft_lstclear(&list, &free);

int	ft_load_game(t_game *game)
{
	t_list		*list;

	list = ft_locate_items(game->board, C_COLLECTIBLE);
	game->collectibles = list;
	game->n_collectible = ft_lstsize(list);
	if (list)
		ft_lstclear(&list, &free);
	list = ft_locate_items(game->board, C_EXIT);
	if (list)
		game->exit = (t_vector *) list->content;
	game->n_exit = ft_lstsize(list);
	if (list)
		ft_lstclear(&list, &free);
	list = ft_locate_items(game->board, C_PLAYER);
	if (list)
		game->player = (t_vector *) list->content;
	game->n_player = ft_lstsize(list);
	if (list)
		ft_lstclear(&list, &free);
	if (game->player == NULL)
		game->player = ft_isghost_player(game->player);
	return (0);
}

static t_vector	*ft_isghost_player(t_vector *player)
{
	if (player == NULL)
	{
		player = (t_vector *) ft_calloc(1, sizeof(t_vector));
		player->x = 1;
		player->y = 1;
	}
	return (player);
}
