/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:27:10 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/04 20:24:21 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	new_image(t_data *d, t_img *img, char *path)
{
	img->ptr = mlx_xpm_file_to_image(d-> mlx, path, &img->width, &img->height);
	if (!img->ptr)
		exit_and_free(d, IMG_ERROR);
	img->addr = (unsigned int *)mlx_get_data_addr(img->ptr,
			&img->bits_per_pixel, &img->line_length, &img->endian);
}

void	create_frame_image(t_data *d, t_img *img)
{
	img->ptr = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	img->addr = (unsigned int *)mlx_get_data_addr(img->ptr,
			&img->bits_per_pixel, &img->line_length, &img->endian);
	img->width = WIDTH;
	img->height = HEIGHT;
}

void	copypaste_img(t_img *src, t_img *dest, int start_x, int start_y)
{
	int				x;
	int				y;
	unsigned int	color;

	x = 0;
	y = 0;
	while (y < src->height)
	{
		x = 0;
		while (x < src->width)
		{
			color = mlx_get_pixel(src, x, y);
			if (color != 0xFF000000)
				mlx_set_pixel(dest, x + start_x, y + start_y, color);
			x++;
		}
		y++;
	}
}

void	load_game_images(t_data *d)
{
	new_image(d, &d->wall[NO], d->c.no);
	new_image(d, &d->wall[SO], d->c.so);
	new_image(d, &d->wall[EA], d->c.ea);
	new_image(d, &d->wall[WE], d->c.we);
}
