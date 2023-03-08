/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:30:48 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/03/08 17:11:25 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

enum e_game { Stopped = 0, Running, Paused, Stopping, Ended }	state;
enum e_event { ON_KEYDOWN = 2, ON_KEYUP = 3, ON_DESTROY = 17 }	event;
enum e_character { None = 0, Left, Right, Up, Down }			direction;

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
	size_t				width;
	size_t				height;
	t_list				*list;
	int					**board;
}						t_map;

typedef struct s_game
{
	void				*mlx;
	void				*mlx_window;
	enum e_game			state;
	size_t				size;
	size_t				width;
	size_t				height;
	int					**board;
	t_imgdata			*i_floor;
	t_imgdata			*i_wall;
	t_imgdata			*i_collectible;
	t_imgdata			*i_exit;
	t_imgdata			*i_player;
	t_imgdata			*i_blur;
	t_imgdata			*i_pause;
	t_list				*collectibles;
	t_vector			*exit;
	t_vector			*player;
	size_t				n_moves;
	size_t				n_collectible;
	size_t				n_exit;
	size_t				n_player;
}						t_game;

int				ft_load_map(t_map *map);
void			ft_load_map_data(t_map *map);
int				ft_check_map(t_map *map);
int				ft_load_board(t_map *map);

void			ft_map2array(t_map *map);
void			ft_exit(char *str, int num);
int				ft_extension_isvalid(char *filename, char *ext);
int				ft_edit_map(char *filename);
int				ft_write_empty_map(char *filename, int x, int y);
void			ft_delete_nl(void *ptr);
t_map			*ft_new_map(void);
int				**ft_new_board(size_t x, size_t y);
int				ft_launch_game(t_map *map);
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

int				ft_state_render(t_game *game);
int				ft_keycode(int keycode, t_game *game);
int				ft_display_help(void);
void			ft_write_map(t_map *map);

int				ft_set_direction(enum e_character move, t_vector *d);
t_vector		*ft_locate_character(int **board, int c);
int				ft_slide(t_game *game, t_vector *player, t_vector *d);

int				ft_display_nmoves(t_game *game, int n, int background);
int				ft_move(t_game *game, t_vector *player, int keycode);

int				ft_ismovekey(int keycode);

static int		ft_ismovable(t_game *game, t_vector *character,
				t_vector *d, int keycode);
int				ft_ended(t_game *game);

#ifdef GENERATOR

int	main(int argc, char **argv)
{
	t_map	*map;
	t_game	*game;

	if (argc != 2 && argc != 4)
		return (ft_display_help());
	map = ft_new_map();
	map->filename = argv[1];
	if (ft_extension_isvalid(argv[1], MAP_EXT) == 0)
		map->filename = ft_strjoin(argv[1], MAP_EXT);
	if (argc == 4)
		ft_write_empty_map(map->filename, ft_atoi(argv[3]), ft_atoi(argv[2]));
	//better if ft_generate_empty_map (array). so it can be random as well
	ft_load_map(map);
	ft_load_map_data(map);
	ft_load_board(map);
	game = ft_new_game(map);
	ft_lstclear(&map->list, &free);
	ft_load_game(game);
	ft_launch_game(map); //only launch!! do not ft_check.
	//write_map();
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

	map = ft_new_map();
	if (argc == 1 || argv[1] == NULL || *argv[1] == '\0')
		map->filename = "maps/default.ber";
	else if (argc == 2)
		map->filename = argv[1];
	else
		return (ft_display_help()); // exit with some error
	ft_load_map(map);
	ft_load_map_data(map);
	ft_check_map(map);
	ft_load_board(map);
	ft_lstclear(&map->list, &free);
	ft_launch_game(map);
	free(map);
	return (0);
}

int	ft_display_help(void)
{
	ft_printf("usage: ./bonus file\n");
	return (0);
}

#endif

int	ft_launch_game(t_game *game)
{
	ft_memload_images(game); // error if return == 0
	ft_put_images(game);
	mlx_hook(game->mlx_window, ON_KEYDOWN, 0, &ft_keycode, game);
	mlx_hook(game->mlx_window, ON_DESTROY, 0, &ft_destroy, game);
	//mlx_loop_hook(game->mlx, &ft_state_render, game);
	mlx_loop(game->mlx);
	return (0);
}

int	ft_state_render(t_game *game)
{
	mlx_do_sync(game->mlx);
	if (game->state == Stopping)
		ft_destroy(game);
	else if (game->n_collectible == 0 && game->n_exit != 0)
	{
		//ft_log("Obtained all collectibles");
		game->board[game->exit->x][game->exit->y] = C_EXIT;
		ft_put_img(game, game->i_exit, game->exit->x, game->exit->y);
		game->n_exit = 0;
	}
	return (0);
}

t_game	*ft_new_game(t_map *map)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game)); //exit if error oc
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
	game->mlx = mlx_init();
	game->mlx_window = ft_new_window(game, "so_long");
	return (game);
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

void	ft_load_map_data(t_map *map)
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
	int		fd;

	map->list = NULL;
	if (ft_extension_isvalid(map->filename, MAP_EXT) == 0)
		exit (2); // exit with invalid extension error
	fd = open(map->filename, O_RDONLY);
	if (fd == -1)
		exit (2); // exit with some error
	if (read(fd, NULL, 0) != 0)
		exit (2); // exit with som error
	line = get_next_line(fd);
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
	// allocate map // load into list // parse stuff
	close(fd);
	return (0);
}

t_map	*ft_new_map(void)
{
	t_map	*map;

	map = ft_calloc(sizeof(t_map), 1);
	if (map == NULL)
		exit (0); // error if null
	map->filename = NULL;
	map->width = 0;
	map->height = 0;
	map->list = NULL;
	map->board = NULL;
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

#ifdef GENERATOR

int	ft_keycode(int keycode, t_game *game)
{
	if (ft_ismovekey(keycode) != 0)
		ft_move(game, game->player, keycode);
	else if (keycode == KEY_ESC)
	{
		ft_printf("Saved map: filename\n");
		//ft_write_map(game->map);
		ft_destroy(game);
	}
	if (keycode == KEY_1)
		game->board[game->player->x][game->player->y] \
			= C_WALL;
	else if (keycode == KEY_0)
		game->board[game->player->x][game->player->y] \
			= C_EMPTY_SPACE;
	else if (keycode == KEY_C)
		game->board[game->player->x][game->player->y] \
			= C_COLLECTIBLE;
	else if (keycode == KEY_P)
		game->board[game->player->x][game->player->y] \
			= C_PLAYER;
	else if (keycode == KEY_E)
		game->board[game->player->x][game->player->y] \
			= C_EXIT;
	ft_put_default_img(game, game->player->x, game->player->y);
	ft_put_img(game, game->i_blur, game->player->x, game->player->y);
	return (0);
}

#else /* ifndef GENERATOR */

int	ft_keycode(int keycode, t_game *game)
{
	/*
	if (ft_ismovekey(keycode) != 0)
		ft_move(game, game->player, keycode);
	else if (keycode == KEY_PAUSE)
		ft_toggle_pause(game);
	else if (keycode == KEY_ESC)
		ft_destroy(game);
	*/
	if (keycode == KEY_ESC)
		ft_destroy(game);
	return (0);
}

#endif

void	ft_write_map(t_map *map)
{
	size_t		x;
	size_t		y;
	int			fd;

	fd = open(map->filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
	x = 0;
	while (x < map->height)
	{
		y = 0;
		while (y < map->width)
		{
			write(fd, &map->board[x][y], 1);
			y++;
		}
		write(fd, "\n", 1);
		x++;
	}
	ft_printf("Saved map: %s\n", map->filename);
}

#define VEL 4

#ifdef GENERATOR

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
	ft_put_default_img(game, player->x, player->y);
	ft_put_img(game, game->i_player, player->x + d->x, player->y + d->y);
	return (0);
}

#else /* ifndef GENERATOR */

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

int	ft_set_direction(enum e_character move, t_vector *d)
{
	d->x = 0;
	d->y = 0;
	if (move == Left)
		d->y = -1;
	else if (move == Right)
		d->y = 1;
	else if (move == Up)
		d->x = -1;
	else if (move == Down)
		d->x = 1;
	return (move);
}

// t_vector d -> direction

#ifdef GENERATOR

int	ft_move(t_game *game, t_vector *player, int keycode)
{
	t_vector	d;

	if (game->state != Running)
		return (0);
	if (ft_ismovable(game, game->player, &d, keycode) == 0)
		return (0);
	ft_slide(game, player, &d);
	player->x += d.x;
	player->y += d.y;
	ft_put_default_img(game, player->x, player->y);
	mlx_do_sync(game->mlx);
	return (0);
}

static int	ft_ismovable(t_game *game, t_vector *character,
				t_vector *d, int keycode)
{
	enum e_character	move;
	size_t				cx;
	size_t				cy;

	move = ft_ismovekey(keycode);
	if (move == None)
		return (0);
	ft_set_direction(move, d);
	cx = character->x + d->x;
	cy = character->y + d->y;
	if (cx == 0 || cx == game->height - 1
		|| cy == 0 || cy == game->width - 1)
		return (0);
	return (move);
}

#else /* ifndef GENERATOR */

int	ft_move(t_game *game, t_vector *player, int keycode)
{
	t_vector	d;

	if (game->state != Running)
		return (0);
	if (ft_ismovable(game, game->player, &d, keycode) == 0)
		return (0);
	game->board[player->x][player->y] = C_EMPTY_SPACE;
	game->board[player->x + d.x][player->y + d.y] = C_PLAYER;
	ft_slide(game, player, &d);
	ft_put_default_img(game, player->x, player->y);
	player->x += d.x;
	player->y += d.y;
	ft_put_default_img(game, player->x, player->y);
	mlx_do_sync(game->mlx);
	ft_display_nmoves(game, ++game->n_moves, 1);
	return (0);
}

static int	ft_ismovable(t_game *game, t_vector *character,
				t_vector *d, int keycode)
{
	enum e_character	move;
	size_t				cx;
	size_t				cy;

	move = ft_ismovekey(keycode);
	if (move == None)
		return (0);
	ft_set_direction(move, d);
	cx = character->x + d->x;
	cy = character->y + d->y;
	if (game->board[cx][cy] == C_WALL)
		return (0);
	else if (game->board[cx][cy] == C_COLLECTIBLE)
		game->n_collectible--;
	else if (game->board[cx][cy] == C_EXIT
		&& game->n_collectible == 0)
		ft_ended(game);
	return (move);
}

#endif

int	ft_display_nmoves(t_game *game, int n, int background)
{
	int			x;
	int			y;
	int			digits;

	if (LOG_LEVEL > 0)
		ft_printf("> Moves: %d\n", game->n_moves);
	x = game->height - (game->size / 2) + 3;
	y = (game->width - 1) / 2;
	digits = ft_count_digits(n, 10);
	if (background != 0)
	{
		ft_put_default_img(game, x / game->size, y / game->size);
		ft_put_default_img(game, x / game->size, (y + game->size) / game->size);
	}
	mlx_string_put(game->mlx, game->mlx_window, y, x, 0x00F6CDAF, ft_itoa(n));
	return (0);
}

int	ft_ismovekey(int keycode)
{
	enum e_character	direction;

	direction = None;
	if (keycode == KEY_UP || keycode == KEY_W)
		direction = Up;
	else if (keycode == KEY_DOWN || keycode == KEY_S)
		direction = Down;
	else if (keycode == KEY_RIGHT || keycode == KEY_D)
		direction = Right;
	else if (keycode == KEY_LEFT || keycode == KEY_A)
		direction = Left;
	return (direction);
}

int	ft_ended(t_game *game)
{
	game->state = Ended;
	return (0);
}

t_vector	*ft_locate_character(int **board, int c)
{
	t_vector	*coordinates;
	int			x;
	int			y;

	coordinates = ft_calloc(1, sizeof(t_vector));
	x = 0;
	while (coordinates && board[x] != NULL)
	{
		y = 0;
		while (board[x][y] != '\0')
		{
			if (board[x][y] == c)
			{
				coordinates->x = x;
				coordinates->y = y;
				return (coordinates);
			}
			y++;
		}
		x++;
	}
	return (NULL);
}
