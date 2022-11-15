/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:31:20 by mpuig-ma          #+#    #+#             */
/*   Updated: 2022/11/15 12:31:23 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

void	ft_log(char *error_msg, ...)
{
	if (LOG_LEVEL > 0 && *error_msg != '\0')
	{
		ft_putstr_fd("\033[0;93m", 1);
		ft_putstr_fd("log: ", 1);
		ft_putstr_fd(error_msg, 1);
		ft_putstr_fd("\033[0m", 1);
		ft_putchar_fd('\n', 1);
	}
}
