/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:01:57 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/24 09:29:00 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_log(char *str)
{
	while (LOG_LEVEL > 0 && *str != '\0')
		write(1, str++, 1);
}

void	ft_log_state(enum e_game state)
{
	if (state == Paused)
		ft_log("> Paused\n");
	else if (state == Running)
		ft_log("> Running\n");
	else if (state == Stopped)
		ft_log("> Stopped\n");
	else if (state == Stopping)
		ft_log("> Stopping\n");
}
