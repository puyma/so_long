/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:27:35 by mpuig-ma          #+#    #+#             */
/*   Updated: 2022/10/10 18:52:02 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

// t_map ft_check_map(int fd);

int	ft_check_map(int fd)
{
	char	*line;

	line = get_next_line(fd);
	printf("line> %s\n", line);
	write(1, "Map> OK\n", 8);
	return (0);
}
