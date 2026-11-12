/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_drawing_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:20:15 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 17:21:51 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	mlx_set_pixel(t_img *img, int x, int y, int color)
{
	int	pixel;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	pixel = y * img->width + x;
	img->addr[pixel] = color;
}

void	copypaste_img(t_img *src, t_img *dest, int start_x, int start_y)
{
	int				x;
	int				y;
	unsigned int	color;

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

void	copypaste_img_limit(t_img *sc, t_img *dt, t_ivector st, t_ivector lim)
{
	int				x;
	int				y;
	unsigned int	color;

	y = 0;
	while (y < lim.y && y < sc->height)
	{
		x = 0;
		while (x < lim.x && x < sc->width)
		{
			color = mlx_get_pixel(sc, x, y);
			if (color != 0xFF000000)
				mlx_set_pixel(dt, x + st.x, y + st.y, color);
			x++;
		}
		y++;
	}
}

void	draw_numbers(t_data *d, int number, t_ivector start)
{
	int		i;
	int		offset;
	char	*str;
	int		index;

	str = ft_itoa(number);
	i = 0;
	offset = 0;
	while (str[i])
	{
		index = str[i] - 48;
		copypaste_img(&d->numbers[index], &d->i, start.x + offset, start.y);
		offset += d->numbers[index].width;
		i++;
	}
	free(str);
}

void	draw_square(t_data *d, t_ivector pos, int size, unsigned int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			mlx_set_pixel(&d->i, pos.x + x, pos.y + y, color);
			x++;
		}
		y++;
	}
}
