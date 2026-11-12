/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_image_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:16:35 by injah             #+#    #+#             */
/*   Updated: 2025/09/19 17:26:03 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	new_image(t_data *d, t_img *img, char *path)
{
	img->ptr = mlx_xpm_file_to_image(d-> mlx, path, &img->width, &img->height);
	if (!img->ptr)
	{
		ft_dprintf(2, "%s missing\n", path);
		exit_and_free(d, IMG_ERROR);
	}
	img->addr = (unsigned int *)mlx_get_data_addr(img->ptr,
			&img->bits_per_pixel, &img->line_length, &img->endian);
}

int	new_image_ret(t_data *d, t_img *img, char *path)
{
	img->ptr = mlx_xpm_file_to_image(d-> mlx, path, &img->width, &img->height);
	if (!img->ptr)
	{
		ft_dprintf(2, "%s failed load\n", path);
		return (-1);
	}
	img->addr = (unsigned int *)mlx_get_data_addr(img->ptr,
			&img->bits_per_pixel, &img->line_length, &img->endian);
	return (0);
}

void	create_frame_image(t_data *d, t_img *img)
{
	img->ptr = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	img->addr = (unsigned int *)mlx_get_data_addr(img->ptr,
			&img->bits_per_pixel, &img->line_length, &img->endian);
	img->width = WIDTH;
	img->height = HEIGHT;
}

unsigned int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	mlx_get_pixel(t_img *img, int x, int y)
{
	int	pixel_index;
	int	color;

	pixel_index = y * img->width + x;
	color = img->addr[pixel_index];
	return (color);
}
