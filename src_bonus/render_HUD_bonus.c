/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_HUD_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:00:08 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 16:52:41 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static void	health_bar(t_data *d)
{
	t_ivector	start;
	t_ivector	limit;

	start.x = 200;
	start.y = 725;
	limit.x = d->health->width * ((float)d->p.life / d->p.life_max);
	limit.y = d->health->height;
	copypaste_img(&d->health_empty, &d->i, start.x, start.y);
	copypaste_img_limit(&d->health[d->p.powered], &d->i, start, limit);
}

static void	fill_sprint_bar(t_data *d, t_img *bar)
{
	int		y;
	int		x;
	int		filled;

	filled = (int)(bar->width * (d->p.stamina / d->p.stamina_max));
	y = 0;
	while (y <= bar->height)
	{
		x = 0;
		while (x <= bar->width)
		{
			if (x <= filled)
				mlx_set_pixel(bar, x, y, 0x2c501a);
			else
				mlx_set_pixel(bar, x, y, RED);
			x++;
		}
		y++;
	}
}

static void	make_sprint_bar(t_data *d)
{
	t_img	bar;

	bar.ptr = mlx_new_image(d->mlx, d->border[0].width, d->border[0].height);
	bar.addr = (unsigned int *)mlx_get_data_addr(bar.ptr,
			&bar.bits_per_pixel, &bar.line_length, &bar.endian);
	bar.width = d->border[0].width;
	bar.height = d->border[0].height;
	fill_sprint_bar(d, &bar);
	copypaste_img(&bar, &d->i, 200, 780 - bar.height);
	copypaste_img(&d->border[d->p.powered], &d->i, 200, 780 - bar.height);
	mlx_destroy_image(d->mlx, bar.ptr);
}

void	hud(t_data *d)
{
	minimap(d);
	change_minimap_size(d);
	copypaste_img(&d->status[d->p.powered], &d->i, 0,
		HEIGHT - d->status[d->p.powered].height);
	make_sprint_bar(d);
	health_bar(d);
	copypaste_img(&d->crosshair, &d->i, MIWIDTH - d->crosshair.width / 2,
		MIHEIGHT - d->crosshair.height / 2);
	draw_numbers(d, d->p.kill_count, (t_ivector){785, 713});
	draw_numbers(d, d->p.level, (t_ivector){789, 744});
	draw_numbers(d, d->p.xp, (t_ivector){745, 777});
}
