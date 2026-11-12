/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:02:30 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 16:51:01 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static void	calculate_horizon(t_data *d, t_floorcast *fc, int y)
{
	fc->p = y - MIHEIGHT;
	fc->row_dist = fc->pos_z / fc->p;
	fc->floor_step.x = fc->row_dist * fc->step.x;
	fc->floor_step.y = fc->row_dist * fc->step.y;
	fc->floor.x = d->p.pos.x + fc->row_dist * fc->ray_dir_l.x;
	fc->floor.y = d->p.pos.y + fc->row_dist * fc->ray_dir_l.y;
}

static void	floor_texture_coordinate(t_data *d, t_floorcast *fc, int panner)
{
	fc->cell.x = (int)(fc->floor.x);
	fc->cell.y = (int)(fc->floor.y);
	if (!is_out_of_map(d->c.cols, d->c.rows, fc->cell.x, fc->cell.y))
		fc->cell_case = d->c.map[fc->cell.y][fc->cell.x];
	else
		fc->cell_case = '\0';
	if (fc->cell_case == CASE_RIVER && d->c.river_path)
	{
		fc->floor_img = &d->river;
		fc->uv.x = (int)(fc->floor_img->width * (fc->floor.x - fc->cell.x)
				+ panner) & (fc->floor_img->width - 1);
		fc->uv.y = (int)(fc->floor_img->height * (fc->floor.y - fc->cell.y))
			& (fc->floor_img->height - 1);
	}
	else
	{
		fc->floor_img = &d->floor;
		fc->uv.x = (int)(fc->floor_img->width * (fc->floor.x - fc->cell.x))
			& (fc->floor_img->width - 1);
		fc->uv.y = (int)(fc->floor_img->height * (fc->floor.y - fc->cell.y))
			& (fc->floor_img->height - 1);
	}
}

static void	drawfr(t_data *d, t_floorcast *fc, int x, int y)
{
	unsigned int	color;

	color = fc->floor_img->addr[fc->floor_img->width * fc->uv.y + fc->uv.x];
	if (d->light == false)
		color = (color >> 1) & 0x7f7f7f;
	mlx_set_pixel(&d->i, x, y, color);
	d->z_buffer[y * WIDTH + x] = fc->row_dist;
	if (d->c.roof_path && !is_out_of_map(d->c.cols,
			d->c.rows, fc->cell.x, fc->cell.y)
		&& (d->c.map[fc->cell.y][fc->cell.x] == CASE_ROOF
		|| d->c.map[fc->cell.y][fc->cell.x] == CASE_ODOOR))
	{
		fc->uv.x = (int)(d->roof.width * (fc->floor.x - fc->cell.x))
			& (d->roof.width - 1);
		fc->uv.y = (int)(d->roof.height * (fc->floor.y - fc->cell.y))
			& (d->roof.height - 1);
		color = d->roof.addr[d->roof.width * fc->uv.y + fc->uv.x];
		mlx_set_pixel(&d->i, x, HEIGHT - y - 1, color);
		d->z_buffer[(HEIGHT - y - 1) * WIDTH + x] = fc->row_dist;
	}
}

void	floorcasting(t_data *d)
{
	t_floorcast		fc;
	static int		panner = 0;
	int				x;
	int				y;

	panner++;
	y = MIHEIGHT;
	init_floorcasting(d, &fc);
	while (++y < HEIGHT)
	{
		calculate_horizon(d, &fc, y);
		x = -1;
		while (++x < WIDTH)
		{
			if (d->z_buffer[y * WIDTH + x] < fc.row_dist)
			{
				fc.floor.x += fc.floor_step.x;
				fc.floor.y += fc.floor_step.y;
				continue ;
			}
			(floor_texture_coordinate(d, &fc, panner), drawfr(d, &fc, x, y));
			fc.floor.x += fc.floor_step.x;
			fc.floor.y += fc.floor_step.y;
		}
	}
}
