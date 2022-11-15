/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:15:09 by mpuig-ma          #+#    #+#             */
/*   Updated: 2022/11/15 16:56:56 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

void	ft_exit_error(int error_num)
{
	ft_putstr_fd("Error: ", 1);
	ft_putstr_fd(strerror(error_num), 1);
	ft_putstr_fd(" [", 1);
	ft_putnbr_fd(error_num, 1);
	ft_putstr_fd("]", 1);
	ft_putchar_fd('\n', 1);
	exit(error_num);
}

void	ft_exit_error_str(char *error_str, int error_num)
{
	ft_putstr_fd("Error: ", 1);
	ft_putstr_fd(error_str, 1);
	ft_putstr_fd(" [", 1);
	ft_putnbr_fd(error_num, 1);
	ft_putstr_fd("]", 1);
	ft_putchar_fd('\n', 1);
	exit(error_num);
}
