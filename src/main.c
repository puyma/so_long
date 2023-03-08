/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:30:48 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/03/07 13:19:23 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

enum e_game { Stopped = 0, Running, Paused, Stopping, Ended }	state;
enum e_event { ON_KEYDOWN = 2, ON_KEYUP = 3, ON_DESTROY = 17 }	event;

typedef struct s_imgdata
{
	void				*img;
	char				*address;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	int					width;
	int					height;
}						t_imgdata;

typedef struct s_vector
{
	int					x;
	int					y;
}						t_vector;

typedef struct s_map
{
	char				*filename;
	int					fd;
	size_t				width;
	size_t				height;
	int					**board;
	t_list				*list;
	t_list				*collectibles;
	t_vector			*player;
	t_vector			*exit;
	int					n_collectible;
	int					n_exit;
	int					n_player;
}						t_map;

typedef struct s_game
{
	void				*mlx;
	void				*mlx_window;
	enum e_game			state;
	size_t				size;
	size_t				width;
	size_t				height;
	size_t				n_moves;
	int					**board;
	t_imgdata			*i_floor;
	t_imgdata			*i_wall;
	t_imgdata			*i_collectible;
	t_imgdata			*i_exit;
	t_imgdata			*i_player;
	t_imgdata			*i_blur;
	t_imgdata			*i_pause;
}						t_game;

int				ft_load_map(t_map *map);
void			ft_exit(char *str, int num);
int				ft_extension_isvalid(char *filename, char *ext);
int				ft_edit_map(char *filename);
int				ft_write_empty_map(char *filename, int x, int y);
int				ft_check_map(t_map *map);
void			ft_delete_nl(void *ptr);
void			ft_parse_map(t_map *map);
void			ft_map2array(t_map *map);
t_map			*ft_new_map(void);
int				ft_set_board(t_map *map);
int				**ft_new_board(size_t x, size_t y);
int				ft_launch(t_map *map);
t_game			*ft_new_game(t_map *map);
int				ft_state_render(t_game *game);
int				ft_destroy(t_game *game);
int				ft_ended(t_game *game);
int				ft_keycode(int keycode, t_game *game);
void			*ft_new_window(t_game *game, char *title);
int				ft_destroy(t_game *game);
int				ft_memload_images(t_game *game);
t_imgdata		*ft_memload_img(t_game *game, char *filename);
void			ft_memunload_images(t_game *game);

int				ft_put_images(t_game *game);
int				ft_put_default_img(t_game *game, int x, int y);
int				ft_put_img(t_game *game, t_imgdata *img, int x, int y);
int				ft_put_img_xy(t_game *game, t_imgdata *img, int x, int y);

#ifndef GENERATOR

int	main(int argc, char **argv)
{
	t_map	*map;

	map = ft_new_map();
	if (argc == 1 || argv[1] == NULL || *argv[1] == '\0')
		map->filename = "maps/default.ber";
	else if (argc == 2)
		map->filename = argv[1];
	else
		return (0); // exit with some error
	ft_load_map(map);
	ft_parse_map(map);
	//ft_check_map(map);
	ft_set_board(map);
	ft_lstclear(&map->list, &free);
	ft_launch(map);
	free(map);
	return (0);
}

#else

int	main(int argc, char **argv)
{
	t_map	*map;

	if (argc != 2 && argc != 4)
		return (0);
	map = ft_new_map();
	map->filename = argv[1];
	if (ft_extension_isvalid(argv[1], MAP_EXT) == 0)
		map->filename = ft_strjoin(argv[1], MAP_EXT);
	if (argc == 4)
		ft_write_empty_map(map->filename, ft_atoi(argv[3]), ft_atoi(argv[2]));
	//better if ft_generate_empty_map (array). so it can be random as well
	ft_load_map(map);
	ft_parse_map(map);
	ft_set_board(map);
	ft_lstclear(&map->list, &free);
	ft_launch(map); //only launch!! do not ft_check.
	free(map);
	return (0);
}

#endif

int	ft_launch(t_map *map)
{
	t_game	*game;

	game = ft_new_game(map);
	ft_memload_images(game); // error if return == 0
	ft_put_images(game);
	//mlx_hook(game->mlx_window, ON_KEYDOWN, 0, &ft_keycode, game);
	mlx_hook(game->mlx_window, ON_DESTROY, 0, &ft_destroy, game);
	//mlx_loop_hook(game->mlx, &ft_state_render, game);
	mlx_loop(game->mlx);
	return (0);
}

t_game	*ft_new_game(t_map *map)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game)); //exit if error oc
	game->size = PIX_SIZE;
	game->board = map->board;
	game->n_moves = 0;
	game->width = map->width * game->size;
	game->height = map->height * game->size;
	game->mlx = mlx_init();
	game->mlx_window = ft_new_window(game, "so_long");
	return (game);
}

int	ft_set_board(t_map *map)
{
	map->board = ft_new_board(map->width, map->height);
	ft_map2array(map);
	return (0);
}

int	**ft_new_board(size_t x, size_t y)
{
	int		**board;
	size_t	i;

	board = (int **) ft_calloc(y + 1, sizeof(int *)); // exit if NULL
	i = 0;
	while (i < y)
		board[i++] = (int *) ft_calloc(x, sizeof(int));
	return (board);
}

void	ft_map2array(t_map *map)
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

void	ft_parse_map(t_map *map)
{
	t_list	*l;
	size_t	len;

	l = map->list;
	map->height = ft_lstsize(map->list);
	while (l != NULL) // might as well write this into ft_lstiter
	{
		len = ft_strlen(l->content);
		if (len > map->width)
			map->width = len;
		l = l->next;
	}
}

int	ft_load_map(t_map *map)
{
	char	*line;

	map->list = NULL;
	if (ft_extension_isvalid(map->filename, MAP_EXT) == 0)
		exit (2); // exit with invalid extension error
	map->fd = open(map->filename, O_RDONLY);
	if (map->fd == -1)
		exit (2); // exit with some error
	if (read(map->fd, NULL, 0) != 0)
		exit (2); // exit with som error
	line = get_next_line(map->fd);
	while (line != NULL)
	{
		if (*line != '#' && !ft_isspace(*line))
			ft_lstadd_back(&map->list, ft_lstnew(line));
		else
			free(line);
		line = get_next_line(map->fd);
	}
	ft_lstiter(map->list, &ft_delete_nl);
	map->height = ft_lstsize(map->list);
	// allocate map // load into list // parse stuff
	close(map->fd);
	return (0);
}

t_map	*ft_new_map(void)
{
	t_map	*map;

	map = ft_calloc(sizeof(t_map), 1);
	if (map == NULL)
		exit (0); // error if null
	map->filename = NULL;
	map->fd = 0;
	map->width = 0;
	map->height = 0;
	map->board = NULL;
	map->list = NULL;
	map->collectibles = 0;
	map->player = NULL;
	map->exit = NULL;
	map->n_collectible = 0;
	map->n_exit = 0;
	map->n_player = 0;
	return (map);
}

int	ft_check_map(t_map *map)
{
	(void) map;
	return (0);
	// with everything parsed, determinate if the map is valid for the game
}

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

int	ft_edit_map(char *filename)
{
	(void) filename;
	return (0);
}

int	ft_write_empty_map(char *filename, int x, int y)
{
	if (x < 1 || y < 1)
		return (0); // exit with some error!
	(void) filename;
	return (0);
}

void	ft_exit(char *error_str, int error_num)
{
	if (*error_str == '\0')
		error_str = strerror(error_num);
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(error_str, 1);
	ft_putstr_fd(" [", 1);
	ft_putnbr_fd(error_num, 1);
	ft_putstr_fd("]", 1);
	ft_putchar_fd('\n', 1);
	exit(error_num);
}

int	ft_extension_isvalid(char *filename, char *ext)
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

void	*ft_new_window(t_game *game, char *title)
{
	void	*window;

	window = NULL;
	window = mlx_new_window(game->mlx, game->width, game->height, title);
	return (window);
}

int	ft_destroy(t_game *game)
{
	mlx_clear_window(game->mlx, game->mlx_window);
	//game->state = Stopping;
	//ft_log_state(game->state);
	mlx_destroy_window(game->mlx, game->mlx_window);
	//game->state = Stopped;
	//ft_log_state(game->state);
	/*
	free(game->i_floor->img);
	free(game->i_wall->img);
	free(game->i_collectible->img);
	free(game->i_exit->img);
	free(game->i_player->img);
	free(game->i_blur->img);
	free(game->i_pause->img);
	*/
	// ft_memunload_images(game);
	exit(0);
}

int	ft_memload_images(t_game *game)
{
	game->i_floor = ft_memload_img(game, FLOOR);
	game->i_wall = ft_memload_img(game, WALL);
	game->i_collectible = ft_memload_img(game, COLLECTIBLE);
	game->i_exit = ft_memload_img(game, EXIT);
	game->i_player = ft_memload_img(game, PLAYER);
	if (game->i_floor == NULL
		|| game->i_wall == NULL
		|| game->i_collectible == NULL
		|| game->i_exit == NULL
		|| game->i_player == NULL)
		return (0);
	return (1);
}

// maybe load directly xpm from memory though compilation (no .xpm files)

t_imgdata	*ft_memload_img(t_game *game, char *filename)
{
	t_imgdata	*img;

	img = (t_imgdata *) ft_calloc(sizeof(t_imgdata), 1);
	if (ft_extension_isvalid(filename, ".xpm") != 0)
		img->img = mlx_xpm_file_to_image(game->mlx, filename, \
			&img->width, &img->height);
	if (img->img == NULL)
		ft_exit(ERR_IMG_LOAD, 79);
	img->address = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
			&img->line_length, &img->endian);
	return (img);
}

void	ft_memunload_images(t_game *game)
{
	if (game->i_floor)
		free(game->i_floor);
	if (game->i_wall)
		free(game->i_wall);
	if (game->i_collectible)
		free(game->i_collectible);
	if (game->i_exit)
		free(game->i_exit);
	if (game->i_player)
		free(game->i_player);
}

int	ft_put_images(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (game->board[x] != NULL)
	{
		y = 0;
		while (game->board[x][y] != '\0')
		{
			if (game->board[x][y] == C_EXIT) // && game->map->n_exit != 0)
				ft_put_img(game, game->i_floor, x, y);
			else if (game->board[x][y] == C_EXIT) // && game->map->n_exit == 0)
				ft_put_img(game, game->i_exit, x, y);
			else
				ft_put_default_img(game, x, y);
			y++;
		}
		x++;
	}
	return (0);
}

int	ft_put_default_img(t_game *game, int x, int y)
{
	if (game->board[x][y] == C_WALL)
		ft_put_img(game, game->i_wall, x, y);
	else if (game->board[x][y] == C_EMPTY_SPACE)
		ft_put_img(game, game->i_floor, x, y);
	else if (game->board[x][y] == C_COLLECTIBLE)
		ft_put_img(game, game->i_collectible, x, y);
	else if (game->board[x][y] == C_EXIT)
		ft_put_img(game, game->i_exit, x, y);
	else if (game->board[x][y] == C_PLAYER)
		ft_put_img(game, game->i_player, x, y);
	return (0);
}

int	ft_put_img(t_game *game, t_imgdata *img, int x, int y)
{
	x *= game->size;
	y *= game->size;
	mlx_put_image_to_window(game->mlx, game->mlx_window, img->img, y, x);
	return (0);
}

int	ft_put_img_xy(t_game *game, t_imgdata *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->mlx_window, img->img, y, x);
	return (0);
}
