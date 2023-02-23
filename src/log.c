/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:01:57 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/21 17:02:43 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_log(char *str)
{
	while (*str != '\0')
		write(1, str++, 1);
}

void	ft_log_state(t_game *game)
{
	ft_printf("> state [%d]\n", game->state);
}
