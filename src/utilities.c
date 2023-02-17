/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:28:52 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/17 18:14:31 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_delete_nl(void *ptr)
{
	char	*str;

	str = (char *) ptr;
	while (*str != '\0')
	{
		if (*str == '\n')
			*str = '\0';
		str++;
	}
}

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

void	ft_exit_str(char *error_str, int error_num)
{
	ft_putstr_fd("Error: ", 1);
	ft_putstr_fd(error_str, 1);
	ft_putstr_fd(" [", 1);
	ft_putnbr_fd(error_num, 1);
	ft_putstr_fd("]", 1);
	ft_putchar_fd('\n', 1);
	exit(error_num);
}

int	ft_ismovekey(int keycode)
{
	if (keycode == KEY_UP || keycode == KEY_W)
		return (keycode);
	else if (keycode == KEY_DOWN || keycode == KEY_S)
		return (keycode);
	else if (keycode == KEY_RIGHT || keycode == KEY_D)
		return (keycode);
	else if (keycode == KEY_LEFT || keycode == KEY_A)
		return (keycode);
	return (-1);
}
