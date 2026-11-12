/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:43:03 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/04 20:27:50 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	mlx_set_pixel(t_img *img, int x, int y, int color)
{
	int	pixel;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	pixel = y * img->width + x;
	img->addr[pixel] = color;
}

int	mlx_get_pixel(t_img *img, int x, int y)
{
	int	pixel_index;
	int	color;

	pixel_index = y * img->width + x;
	color = img->addr[pixel_index];
	return (color);
}
