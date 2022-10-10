/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_so_long.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:36:50 by mpuig-ma          #+#    #+#             */
/*   Updated: 2022/10/10 18:56:13 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/src/libft.h"
#include "ft_so_long.h"

int	main(int argc, char **argv)
{
	const char	*input;
	const char	*default_map = "maps/default.ber";

	if (argc == 1)
		ft_launch(default_map);
	else if (argc == 2)
	{
		input = argv[1];
		if (*input == '\0' || ft_isextension(input, ".ber") != 0)
			return (0);
		ft_launch(input);
	}
	return (0);
}
