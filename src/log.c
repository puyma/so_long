/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:01:57 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/24 09:47:10 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_log(char *str)
{
	if (LOG_LEVEL > 0)
	{
		while (*str != '\0')
			write(1, str++, 1);
		write(1, "\n", 1);
	}
}

void	ft_log_state(enum e_game state)
{
	if (state == Paused)
		ft_log("> Paused");
	else if (state == Running)
		ft_log("> Runninn");
	else if (state == Stopped)
		ft_log("> Stoppen");
	else if (state == Stopping)
		ft_log("> Stoppinn");
}
