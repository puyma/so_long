/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_content.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:22:14 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/01/17 19:31:06 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

int	ft_content_isvalid(t_map *map)
{
	t_list	*t;

	t = map->lst;
	while (t != NULL)
	{
		ft_printf("len> %d\n", ft_strlen(t->content));
		if (ft_strlen(t->content) == map->lstsize)
			ft_exit_str("Map should not be square", 69);
		t = t->next;
	}
	return (1);
	return (0);
}
