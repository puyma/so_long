/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_button.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 20:26:09 by mpuig-ma          #+#    #+#             */
/*   Updated: 2022/11/04 20:26:33 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

t_button	*ft_new_button(int w, int h, int x, int y)
{
	t_button	*button;

	button = (t_button *) malloc(sizeof(t_button));
	if (button == NULL)
		return (NULL);
	button->width = w;
	button->height = h;
	button->x = x;
	button->y = y;
	return (button);
}
