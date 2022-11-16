/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:27:35 by mpuig-ma          #+#    #+#             */
/*   Updated: 2022/11/15 16:56:45 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

static int	ft_check_filename(const char *input);
static int	ft_check_fd(const char *input);
static int	ft_check_content(int fd, t_map *map);
static int	ft_iscomment(char *line);

int	ft_check_map(const char *input, t_map *map)
{
	int		fd;

	ft_log("begin map check");
	ft_log((char *)input);
	ft_check_filename(input);
	fd = ft_check_fd(input);
	ft_check_content(fd, map);
	ft_check_path(map);
	write(1, "Map> OK\n", 8);
	return (42);
}

static int	ft_check_filename(const char *input)
{
	int	path_length;

	path_length = ft_strlen(input);
	if (path_length == 0)
		ft_exit_error(22);
	if (path_length > FILENAME_LEN)
		ft_exit_error(63);
	ft_log("length OK");
	if (ft_strncmp((input + path_length - 4), ".ber", 4) != 0)
		ft_exit_error(79);
	ft_log("extension OK");
	return (path_length);
}

static int	ft_check_fd(const char *input)
{
	int	fd;

	fd = open(input, O_RDONLY);
	if (fd == -1)
		ft_exit_error(9);
	if (read(fd, NULL, 0) != 0)
		ft_exit_error_str("Couldn\'t read from file descriptor", 0);
	ft_log("file descriptor OK");
	return (fd);
}

static int	ft_check_content(int fd, t_map *map)
{
	char 	*line;
	t_list	**lines;
	
	line = get_next_line(fd);
	*lines = ft_lstnew(line);
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_iscomment(line) == 0)
			ft_lstadd_back(lines, ft_lstnew(line));
		else
		free(line);
	}
	while (*lines != NULL)
	{
		ft_putendl_fd(*(*(lines->content)), 1);
		lines++;
	}
	//ft_log("content OK");
	return (0);
}

static int	ft_iscomment(char *line)
{
	if (*line == '#' || *line == ' ')
		return (1);
	return (0);
}