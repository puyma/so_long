/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:36:50 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/14 16:56:32 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	const char	*default_map = "maps/default.ber";

	if (argc == 1)
		ft_launch(default_map);
	else if (argc == 2)
		ft_launch(argv[1]);
	else if (argc > 2)
		ft_exit_error(22);
	return (0);
}
