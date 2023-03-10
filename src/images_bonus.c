/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:46:02 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/03/10 15:46:09 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_memload_images(t_game *game)
{
	game->i_floor = ft_memload_img(game, FLOOR);
	game->i_wall = ft_memload_img(game, WALL);
	game->i_collectible = ft_memload_img(game, COLLECTIBLE);
	game->i_exit = ft_memload_img(game, EXIT);
	game->i_player = ft_memload_img(game, PLAYER);
	game->i_blur = ft_memload_img(game, BLUR);
	game->i_pause = ft_memload_img(game, PAUSE);
	if (game->i_floor == NULL
		|| game->i_wall == NULL
		|| game->i_collectible == NULL
		|| game->i_exit == NULL
		|| game->i_player == NULL
		|| game->i_blur == NULL
		|| game->i_pause == NULL)
	{
		ft_memunload_images(game);
		return (0);
	}
	return (1);
}

t_imgdata	*ft_memload_img(t_game *game, char *filename)
{
	t_imgdata	*img;

	img = (t_imgdata *) ft_calloc(sizeof(t_imgdata), 1);
	if (ft_extension_isvalid(filename, ".xpm") != 0)
		img->img = mlx_xpm_file_to_image(game->mlx, filename, \
			&img->width, &img->height);
	else if (ft_extension_isvalid(filename, ".png") != 0)
		img->img = mlx_png_file_to_image(game->mlx, filename, \
			&img->width, &img->height);
	else
		ft_exit(NULL, 69);
	if (img->img == NULL)
		ft_exit(ERR_IMG_LOAD, 79);
	img->address = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
			&img->line_length, &img->endian);
	return (img);
}

void	ft_memunload_images(t_game *game)
{
	if (game->i_floor)
		free(game->i_floor);
	if (game->i_wall)
		free(game->i_wall);
	if (game->i_collectible)
		free(game->i_collectible);
	if (game->i_exit)
		free(game->i_exit);
	if (game->i_player)
		free(game->i_player);
	if (game->i_blur)
		free(game->i_blur);
	if (game->i_pause)
		free(game->i_pause);
}
