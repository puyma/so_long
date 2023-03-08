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

typedef struct s_vector
{
	int			x;
	int			y;
}				t_vector;

typedef struct s_map
{
	char		*filename;
	int			fd;
	size_t		width;
	size_t		height;
	int			**board;
	t_list		*list;
	t_list		*collectibles;
	t_vector	*player;
	t_vector	*exit;
	int			n_collectible;
	int			n_exit;
	int			n_player;
}				t_map;

int		ft_load_map(t_map *map);
void	ft_exit(char *str, int num);
int		ft_extension_isvalid(char *filename, char *ext);
int		ft_edit_map(char *filename);
int		ft_write_empty_map(char *filename, int x, int y);
int		ft_check_map(t_map *map);
void	ft_delete_nl(void *ptr);
void	ft_parse_map(t_map *map);
void	ft_map2array(void *ptr);
t_map	*ft_new_map(void);
int		ft_set_board(t_map *map);

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
	// ft_load_map(map);
	// ft_parse_map(map);
	//ft_check_map(map);
	//ft_map2array(map);
	ft_lstclear(&map->list, &free);
	//ft_launch(map);
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
	//if (argc == 4)
		//ft_write_empty_map(map.filename, ft_atoi(argv[3]), ft_atoi(argv[2]));
		//better if ft_generate_empty_map (array)
	ft_load_map(map);
	ft_parse_map(map);
	ft_set_board(map);
	ft_lstclear(&map->list, &free);
	//ft_launch(map); //only launch!! do not ft_check.
	free(map);
	return (0);
}

#endif

int	**ft_new_board(size_t x, size_t y);

int	ft_set_board(t_map *map)
{
	map->board = ft_new_board(map->width, map->height);
	//int x = ft_lstsize(list);
	//board = ft_calloc(sizeof(int *), );
	ft_lstiter(map->list, &ft_map2array);
	(void) map->board;
	return (0);
}

int	**ft_new_board(size_t x, size_t y)
{
	int	**board;
	
	board = (int **) ft_calloc(y, sizeof(int *)); // exit if NULL
	while (y--)
		board[y] = (int *) ft_calloc(x, sizeof(int));
	/*
	size_t i = 0;
	while (i < y)
	{
		board[i] = (int *) ft_calloc(x, sizeof(int));
		i++;
	}
	*/
	return (board);
}

void	ft_map2array(void *ptr)
{
	(void) ptr;
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
