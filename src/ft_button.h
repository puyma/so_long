/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_button.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:24:15 by mpuig-ma          #+#    #+#             */
/*   Updated: 2022/11/04 22:41:40 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BUTTON_H
# define FT_BUTTON_H

typedef struct s_button {
	int		width;
	int		height;
	int		x;
	int		y;
	void	*click_event;
	void	*hover_event;
}		t_button;

t_button	*ft_new_button(int w, int h, int x, int y);

#endif /* ft_button.h */
