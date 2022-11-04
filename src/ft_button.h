/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_button.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:24:15 by mpuig-ma          #+#    #+#             */
/*   Updated: 2022/11/04 18:30:55 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_button	{
	int		width;
	int		height;
	int		x;
	int		y;
	void	*click_event;
	void	*hover_event;
}		t_button;
