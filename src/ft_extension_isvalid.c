/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extension_isvalid.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:06:00 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/02/28 14:06:01 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_extension_isvalid(char *filename, char *ext)
{
	size_t	path_length;	
	size_t	ext_len;

	path_length = ft_strlen(filename);
	ext_len = ft_strlen(ext);
	if (path_length == 0 || path_length > FILENAME_LEN)
		return (0);
	if (ft_strncmp((filename + path_length - ext_len), ext, ext_len) != 0)
		return (0);
	return ((int) path_length);
}
