/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:27:35 by mpuig-ma          #+#    #+#             */
/*   Updated: 2022/11/04 20:17:35 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

static int	ft_check_filename(const char *input);
static int	ft_check_fd(const char *input);

int	ft_check_map(const char *input)
{
	int		fd;

	ft_log("begin map check");
	ft_log((char *)input);
	ft_check_filename(input);
	fd = ft_check_fd(input);
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
	return (path_length);
}

static int	ft_check_fd(const char *input)
{
	int	fd;

	fd = open(input, O_RDONLY);
	if (fd == -1)
		ft_exit_error(2);
	return (fd);
}
