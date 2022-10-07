/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_so_long.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:36:50 by mpuig-ma          #+#    #+#             */
/*   Updated: 2022/10/07 21:42:53 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/src/libft.h"
#include <unistd.h>
#include <stdio.h>

int	ft_isextension(const char *str, const char *extension)
{
	return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc == 2 && ft_isextension(argv[1], ".ber") != 0)
	{
		write(1, "We are all in this together\n", 29);
	}
	return (0);
}
