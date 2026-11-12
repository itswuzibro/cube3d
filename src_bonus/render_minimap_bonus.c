/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:26:40 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 16:54:08 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	change_minimap_size(t_data *d)
{
	if (d->k.m == true && d->minimap_press == 0)
	{
		d->minimap_size = 8;
		d->minimap_press = 1;
		d->minimap_pix = 5;
		d->k.m = false;
	}
	if (d->k.m == true && d->minimap_press == 1)
	{
		d->minimap_size = 10;
		d->minimap_press = 2;
		d->minimap_pix = 8;
		d->k.m = false;
	}
	if (d->k.m == true && d->minimap_press == 2)
	{
		d->minimap_size = 5;
		d->minimap_press = 0;
		d->minimap_pix = 3;
		d->k.m = false;
	}
}

static void	draw_and_color_square_by_case(t_data *d, int x, int y)
{
	if (d->c.map[y][x] == CASE_WALL)
		draw_square(d, make_ivector(x * d->minimap_pix,
				y * d->minimap_pix), d->minimap_pix, GREY);
	else if (d->c.map[y][x] == CASE_CDOOR)
		draw_square(d, make_ivector(x * d->minimap_pix,
				y * d->minimap_pix), d->minimap_pix, BLOOD);
	else if (d->c.map[y][x] == CASE_RIVER)
		draw_square(d, make_ivector(x * d->minimap_pix,
				y * d->minimap_pix), d->minimap_pix, BLUE);
}

void	minimap(t_data *d)
{
	int	x;
	int	y;

	y = -1;
	while (d->c.map[++y])
	{
		x = 0;
		while (d->c.map[y][x])
		{
			draw_and_color_square_by_case(d, x, y);
			x++;
		}
	}
	draw_square(d, make_ivector(d->p.pos.x * d->minimap_pix,
			d->p.pos.y * d->minimap_pix), d->minimap_pix, GREEN);
	x = 0;
	while (x < MAX_E)
	{
		if (d->enemies[x].active == true && d->enemies[x].state != DEAD)
		{
			draw_square(d, make_ivector(d->enemies[x].pos.x * d->minimap_pix,
					d->enemies[x].pos.y * d->minimap_pix), d->minimap_pix, RED);
		}
		x++;
	}
}
