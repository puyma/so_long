/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:30:48 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/03/09 21:48:22 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

enum e_game { Stopped = 0, Running, Paused, Stopping, Ended }	state;
enum e_event { ON_KEYDOWN = 2, ON_KEYUP = 3, ON_DESTROY = 17 }	event;
enum e_character { None = 0, Left, Right, Up, Down }			direction;

typedef struct s_imgdata
{
	void		*img;
	char		*address;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_imgdata;

typedef struct s_vector
{
	int			x;
	int			y;
}				t_vector;

typedef struct s_map
{
	char		*filename;
	size_t		width;
	size_t		height;
	t_list		*list;
	int			**board;
}				t_map;

typedef struct s_game
{
	void		*mlx;
	void		*mlx_window;
	enum e_game	state;
	size_t		size;
	size_t		width;
	size_t		height;
	int			**board;
	t_imgdata	*i_floor;
	t_imgdata	*i_wall;
	t_imgdata	*i_collectible;
	t_imgdata	*i_exit;
	t_imgdata	*i_player;
	t_imgdata	*i_blur;
	t_imgdata	*i_pause;
	t_list		*collectibles;
	t_vector	*exit;
	t_vector	*player;
	size_t		n_moves;
	size_t		n_collectible;
	size_t		n_exit;
	size_t		n_player;
	char		*filename;
	t_map		*map;
}				t_game;

int				ft_check_map(t_map *map);
void			ft_delete_nl(void *ptr);
int				ft_destroy(t_game *game);
int				ft_destroy(t_game *game);
int				ft_display_help(void);
int				ft_display_nmoves(t_game *game, int n, int background);
int				ft_edit_map(char *filename);
int				ft_ended(t_game *game);
void			ft_exit(char *str, int num);
int				ft_extension_isvalid(char *filename, char *ext);
size_t			ft_get_largest_ln(t_list *list);
t_vector		*ft_isghost_player(t_vector *player);
t_vector		*ft_ismovekey(int keycode);
int				ft_keycode(int keycode, t_game *game);
int				ft_launch(t_game *game);
int				ft_load_board(t_map *map);
int				ft_load_game(t_game *game);
t_vector		*ft_locate_character(int **board, int x, int y, int c);
t_list			*ft_locate_items(int **board, int c);
int				ft_load_map(t_map *map);
void			ft_log(char *str);
void			ft_log_state(enum e_game state);
void			ft_map2array(t_map *map);
int				ft_memload_images(t_game *game);
t_imgdata		*ft_memload_img(t_game *game, char *filename);
void			ft_memunload_images(t_game *game);
int				ft_move(t_game *game, t_vector *player, t_vector *direction);
int				**ft_new_board(size_t x, size_t y);
t_game			*ft_new_game(t_map *map);
t_map			*ft_new_map(char *filename);
void			*ft_new_window(t_game *game, char *title);
int				ft_put_default_img(t_game *game, int x, int y);
int				ft_put_images(t_game *game);
int				ft_put_img(t_game *game, t_imgdata *img, int x, int y);
void			ft_unload_board(int **board);
int				ft_put_img_xy(t_game *game, t_imgdata *img, int x, int y);
int				ft_slide(t_game *game, t_vector *player, t_vector *direction);
int				ft_state_render(t_game *game);
int				ft_write_empty_map(char *filename, int x, int y);
void			ft_write_map(char *filename, int **board);

#ifdef GENERATOR

//better if ft_generate_empty_map (array). so it can be random as well
// if GENERATOR, do not check map, just launch
int	main(int argc, char **argv)
{
	t_map	*map;
	t_game	*game;

	if (argc != 2 && argc != 4)
		return (ft_display_help());
	if (ft_extension_isvalid(argv[1], MAP_EXT) == 0)
		map = ft_new_map(ft_strjoin(argv[1], MAP_EXT));
	else
		map = ft_new_map(argv[1]);
	if (argc == 4)
		ft_write_empty_map(map->filename, ft_atoi(argv[3]), ft_atoi(argv[2]));
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

int	ft_display_help(void)
{
	ft_printf("usage: ./generator file [width] [height]\n");
	return (0);
}

#else /* ifndef GENERATOR */

int	main(int argc, char **argv)
{
	t_map	*map;
	t_game	*game;

	if (argc != 1 && argc != 2)
		return (ft_display_help());
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
	ft_launch(game);
	free(map);
	return (0);
}

int	ft_display_help(void)
{
	ft_printf("usage: ./bonus file\n");
	return (0);
}

#endif

int	ft_launch(t_game *game)
{
	if (ft_memload_images(game) == 0)
		exit (8);
	ft_put_images(game);
	mlx_hook(game->mlx_window, ON_DESTROY, 0, &ft_destroy, game);
	mlx_hook(game->mlx_window, ON_KEYDOWN, 0, &ft_keycode, game);
	mlx_loop_hook(game->mlx, &ft_state_render, game);
	game->state = Running;
	mlx_loop(game->mlx);
	return (0);
}

// ft_put_images -> should only put images, should not do other stuff!
t_game	*ft_new_game(t_map *map)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (game == NULL)
		exit (4);
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
	list = ft_locate_items(game->board, C_EXIT);
	if (list)
		game->exit = (t_vector *) list->content;
	game->n_exit = ft_lstsize(list);
	list = ft_locate_items(game->board, C_PLAYER);
	if (list)
		game->player = (t_vector *) list->content;
	game->n_player = ft_lstsize(list);
	if (game->player == NULL)
		game->player = ft_isghost_player(game->player);
	return (0);
}

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
		exit (10);
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

int	ft_load_board(t_map *map)
{
	map->board = ft_new_board(map->width, map->height);
	ft_map2array(map);
	return (0);
}

int	**ft_new_board(size_t x, size_t y)
{
	int		**board;
	size_t	i;

	board = (int **) ft_calloc(y + 1, sizeof(int *));
	if (board == NULL)
		exit (14);
	i = 0;
	while (i < y)
		board[i++] = (int *) ft_calloc(x + 1, sizeof(int));
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

// ft_get_largest_nl might as well be made into ft_lstiter style
size_t	ft_get_largest_ln(t_list *list)
{
	size_t	len;
	t_list	*l;

	len = 0;
	l = list;
	while (l != NULL)
	{
		if (len < ft_strlen(l->content))
			len = ft_strlen(l->content);
		l = l->next;
	}
	return (len);
}

// exits to manage here
int	ft_load_map(t_map *map)
{
	char	*line;
	int		fd;

	map->list = NULL;
	if (ft_extension_isvalid(map->filename, MAP_EXT) == 0)
		exit (2);
	fd = open(map->filename, O_RDONLY);
	if (fd == -1 || read(fd, NULL, 0) != 0)
		exit (2);
	line = get_next_line(fd);
	if (line == NULL || *line == '\0')
		ft_exit("Your ber is empty, I guess", 16);
	while (line != NULL)
	{
		if (*line != '#' && !ft_isspace(*line))
			ft_lstadd_back(&map->list, ft_lstnew(line));
		else
			free(line);
		line = get_next_line(fd);
	}
	ft_lstiter(map->list, &ft_delete_nl);
	map->height = ft_lstsize(map->list);
	map->width = ft_get_largest_ln(map->list);
	close(fd);
	return (0);
}

// exits to manage here
t_map	*ft_new_map(char *filename)
{
	t_map	*map;

	map = ft_calloc(sizeof(t_map), 1);
	if (map == NULL)
		exit (0);
	map->filename = filename;
	map->width = 0;
	map->height = 0;
	map->list = NULL;
	map->board = NULL;
	return (map);
}

// once everything parsed, determinate if the map is valid for the game
int	ft_check_map(t_map *map)
{
	(void) map;
	return (0);
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

// exits to manage here (return edit)
int	ft_write_empty_map(char *filename, int x, int y)
{
	if (x < 1 || y < 1)
		return (0);
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

	window = mlx_new_window(game->mlx, game->width, game->height, title);
	return (window);
}

int	ft_destroy(t_game *game)
{
	mlx_clear_window(game->mlx, game->mlx_window);
	game->state = Stopping;
	ft_log_state(game->state);
	mlx_destroy_window(game->mlx, game->mlx_window);
	game->state = Stopped;
	ft_log_state(game->state);
	ft_memunload_images(game);
	int x = 0;
	while (game->board[x] != NULL)
	{
		free(game->board[x]);
		x++;
	}
	ft_unload_board(game->board);
	free(game->map);
	exit(0);
}

void	ft_unload_board(int **board)
{
	int	x;

	x = 0;
	while (board[x] != NULL)
		free(board[x++]);
	free(board);
}

int	ft_memload_images(t_game *game)
{
	game->i_floor = ft_memload_img(game, FLOOR);
	game->i_wall = ft_memload_img(game, WALL);
	game->i_collectible = ft_memload_img(game, COLLECTIBLE);
	game->i_exit = ft_memload_img(game, EXIT);
	game->i_player = ft_memload_img(game, PLAYER);
	game->i_blur = ft_memload_img(game, BLUR);
	game->i_pause = ft_memload_img(game, PAUSE);
	if (game->i_floor == NULL
		|| game->i_wall == NULL
		|| game->i_collectible == NULL
		|| game->i_exit == NULL
		|| game->i_player == NULL
		|| game->i_blur == NULL
		|| game->i_pause == NULL)
	{
		ft_memunload_images(game);
		return (0);
	}
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
	else if (ft_extension_isvalid(filename, ".png") != 0)
		img->img = mlx_png_file_to_image(game->mlx, filename, \
			&img->width, &img->height);
	else
		ft_exit(NULL, 69);
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
	if (game->i_blur)
		free(game->i_blur);
	if (game->i_pause)
		free(game->i_pause);
}

#ifdef GENERATOR

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
			ft_put_default_img(game, x, y);
			y++;
		}
		x++;
	}
	return (0);
}

#else /* ifndef GENERATOR */

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
			if (game->board[x][y] == C_EXIT && game->n_exit != 0)
				ft_put_img(game, game->i_floor, x, y);
			else if (game->board[x][y] == C_EXIT && game->n_exit == 0)
				ft_put_img(game, game->i_exit, x, y);
			else
				ft_put_default_img(game, x, y);
			y++;
		}
		x++;
	}
	return (0);
}

#endif

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

t_vector	*ft_isghost_player(t_vector *player)
{
	if (player == NULL)
	{
		player = (t_vector *) ft_calloc(1, sizeof(t_vector));
		player->x = 1;
		player->y = 1;
	}
	return (player);
}

#ifdef GENERATOR

// there may be a leak in here...
int	ft_keycode(int keycode, t_game *game)
{
	t_vector	*player;
	t_vector	*direction;

	player = game->player;
	if (keycode == KEY_ESC)
	{
		ft_write_map(game->filename, game->board);
		ft_destroy(game);
	}
	direction = ft_ismovekey(keycode);
	if (direction != NULL)
		ft_move(game, game->player, direction);
	if (keycode == KEY_1)
		game->board[player->x][player->y] = C_WALL;
	else if (keycode == KEY_0)
		game->board[player->x][player->y] = C_EMPTY_SPACE;
	else if (keycode == KEY_C)
		game->board[player->x][player->y] = C_COLLECTIBLE;
	else if (keycode == KEY_P)
		game->board[player->x][player->y] = C_PLAYER;
	else if (keycode == KEY_E)
		game->board[player->x][player->y] = C_EXIT;
	ft_put_default_img(game, game->player->x, game->player->y);
	ft_put_img(game, game->i_blur, game->player->x, game->player->y);
	return (0);
}

int	ft_move_able(t_game *game, t_vector *player, t_vector *d)
{
	int	cx;
	int	cy;
	int	width;
	int	height;

	cx = player->x + d->x;
	cy = player->y + d->y;
	width = (game->width - 1) / game->size;
	height = (game->height - 1) / game->size;
	if (cx != 0 && cx != height && cy != 0 && cy != width)
		return (1);
	return (0);
}

int	ft_move(t_game *game, t_vector *player, t_vector *d)
{
	if (game->state != Running)
		return (0);
	if (ft_move_able(game, player, d) == 0)
		return (0);
	ft_slide(game, player, d);
	player->x += d->x;
	player->y += d->y;
	ft_put_default_img(game, player->x, player->y);
	mlx_do_sync(game->mlx);
	return (0);
}

#else /* ifndef GENERATOR */

int	ft_keycode(int keycode, t_game *game)
{
	t_vector	*direction;

	if (keycode == KEY_ESC)
		ft_destroy(game);
	else if (keycode == KEY_PAUSE)
		ft_printf("pause\n");
	direction = ft_ismovekey(keycode);
	if (direction != NULL)
		ft_move(game, game->player, direction);
	if (direction)
		free(direction);
	return (0);
}

int	ft_move_able(t_game *game, t_vector *player, t_vector *d)
{
	int	cx;
	int	cy;

	cx = player->x + d->x;
	cy = player->y + d->y;
	if (game->board[cx][cy] == C_WALL)
		return (0);
	else if (game->board[cx][cy] == C_COLLECTIBLE)
		game->n_collectible--;
	else if (game->board[cx][cy] == C_EXIT
		&& game->n_collectible == 0)
		ft_printf("end game\n");
	return (1);
}

int	ft_move(t_game *game, t_vector *player, t_vector *d)
{
	if (game->state != Running)
		return (0);
	if (ft_move_able(game, player, d) == 0)
		return (0);
	game->board[player->x][player->y] = C_EMPTY_SPACE;
	game->board[player->x + d->x][player->y + d->y] = C_PLAYER;
	ft_slide(game, player, d);
	ft_put_default_img(game, player->x, player->y);
	player->x += d->x;
	player->y += d->y;
	ft_put_default_img(game, player->x, player->y);
	mlx_do_sync(game->mlx);
	return (0);
}

#endif

t_vector	*ft_ismovekey(int keycode)
{
	t_vector	*direction;

	direction = ft_calloc(1, sizeof(t_vector));
	if (direction == NULL)
		return (NULL);
	direction->x = 0;
	direction->y = 0;
	if (keycode == KEY_UP || keycode == KEY_W)
		direction->x = -1;
	else if (keycode == KEY_DOWN || keycode == KEY_S)
		direction->x = 1;
	else if (keycode == KEY_RIGHT || keycode == KEY_D)
		direction->y = 1;
	else if (keycode == KEY_LEFT || keycode == KEY_A)
		direction->y = -1;
	return (direction);
}

void	ft_write_map(char *filename, int **board)
{
	size_t		x;
	size_t		y;
	int			fd;

	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
	fd = 1;
	x = 0;
	y = 0;
	while (board[x] != NULL)
	{
		y = 0;
		while (board[x][y] != '\0')
		{
			write(fd, &board[x][y], 1);
			y++;
		}
		write(fd, "\n", 1);
		x++;
	}
	ft_printf("Saved map: %s\n", filename);
}

#ifdef GENERATOR

int	ft_slide(t_game *game, t_vector *player, t_vector *d)
{
	ft_put_default_img(game, player->x, player->y);
	ft_put_img(game, game->i_player, player->x + d->x, player->y + d->y);
	return (0);
}

#else /* ifndef GENERATOR */

# define VEL 4

int	ft_slide(t_game *game, t_vector *player, t_vector *d)
{
	int	size;
	int	px;
	int	py;
	int	i;

	size = game->size;
	px = player->x * size;
	py = player->y * size;
	i = 1;
	while (i <= size)
	{
		ft_put_img_xy(game, game->i_floor, px, py);
		ft_put_img_xy(game, game->i_player, px + (i * d->x), py + (i * d->y));
		mlx_do_sync(game->mlx);
		i += VEL;
	}
	return (0);
}

#endif

int	ft_state_render(t_game *game)
{
	mlx_do_sync(game->mlx);
	if (game->state == Stopping)
		ft_destroy(game);
	else if (game->n_collectible == 0 && game->n_exit != 0)
	{
		ft_log("Obtained all collectibles");
		game->board[game->exit->x][game->exit->y] = C_EXIT;
		ft_put_img(game, game->i_exit, game->exit->x, game->exit->y);
		game->n_exit = 0;
	}
	return (0);
}

void	ft_log(char *str)
{
	if (LOG_LEVEL > 0)
	{
		write(1, "> ", 2);
		while (*str != '\0')
			write(1, str++, 1);
		write(1, "\n", 1);
	}
}

void	ft_log_state(enum e_game state)
{
	if (state == Paused)
		ft_log("Paused");
	else if (state == Running)
		ft_log("Running");
	else if (state == Stopped)
		ft_log("Stopped");
	else if (state == Stopping)
		ft_log("Stopping");
}
