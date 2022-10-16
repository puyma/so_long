/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:27:35 by mpuig-ma          #+#    #+#             */
/*   Updated: 2022/10/16 19:38:53 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

// t_map ft_check_map(int fd);

/*
** strerror: 
** 02: No such file or directory
** 07: Argument list too long
** 09: Bad file descriptor
** 12: Cannot allocate memory
** 13: Permission denied
** 21: Is a directory
** 22: Invalid argument
** 27; File too large
** 28: No space left on device
** 55: No buffer space available
** 63: File name too long
** 71: Too many levels of remote in path
** 79: Inappropriate file type or format
** 105: Previous owner died
*/

/*
** Policy:
** 
** MUST contain at least 1 exit, 1 collectible and 1 starting position.
** MUST be rectangular
** MUST be close/surrounded by walls ; return error (79)
** MUST have a valid path in the map! ft_check_map_path()
** 
** You must be able to parse any kind of map, as long as it respects the above rules. 
** 
** If the map contains duplicate characters (exit/start), you should display an error message (79)
**
** If any misconfiguration of any kind is encountered in the file, the program must exit in a clean 
** way, and return "Error\n" followed by an explicit error message of your choice. 
*/

int	ft_check_map(const char *input)
{
	char	*line;
	int		input_len;

	input_len = ft_strlen(input);
	if (input_len > 42)
	{
		ft_putendl_fd(strerror(63), 1);
		return (63);
	}
	if (*input == '\0')
	{
		// empty input??
		return (0);
	}
	if (ft_strncmp((input + input_len - 4), ".ber", 4) != 0) // faltara comprovar si que l'arxiu no sigui 'res'.ber
	{
		ft_printf("%s\n", strerror(79));
		return (0);
	}
	ft_putstr("Begin map check: ");
	ft_putendl_fd((char *) input, 1);

	(void) line;
	/*
	line = get_next_line(fd);
	int i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != '\n')
			write(1, &line[i], 1);
		i++;
	}
	write(1, "\n", 1);
	*/

	write(1, "Map> OK\n", 8);
	return (0);
}
