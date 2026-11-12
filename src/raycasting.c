/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:36:21 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/17 17:41:12 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	perform_dda(t_data *d, t_raycast *r)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (r->side_dist.x < r->side_dist.y)
		{
			r->side_dist.x += r->delta_dist.x;
			r->map_x += r->step.x;
			r->side = 0;
		}
		else
		{
			r->side_dist.y += r->delta_dist.y;
			r->map_y += r->step.y;
			r->side = 1;
		}
		if (d->c.map[r->map_y][r->map_x] == '1')
			hit = 1;
	}
}

void	calculate_draw_height(t_raycast *r)
{
	if (r->side == 0)
		r->perp_wall_dist = (r->side_dist.x - r->delta_dist.x);
	else
		r->perp_wall_dist = (r->side_dist.y - r->delta_dist.y);
	r->lineheight = (int)(HEIGHT / r->perp_wall_dist);
	r->draw_start = MIHEIGHT - r->lineheight / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = MIHEIGHT + r->lineheight / 2;
	if (r->draw_end > HEIGHT - 1)
		r->draw_end = HEIGHT - 1;
	if (r->side == 0 && r->ray_dir.x > 0)
		r->w = EA;
	else if (r->side == 0 && r->ray_dir.x <= 0)
		r->w = WE;
	else if (r->side == 1 && r->ray_dir.y < 0)
		r->w = NO;
	else
		r->w = SO;
}

void	calculate_texture_coor(t_data *d, t_raycast *r, t_player *p)
{
	if (r->side == 0)
		r->wall_x = p->pos.y + r->perp_wall_dist * r->ray_dir.y;
	else
		r->wall_x = p->pos.x + r->perp_wall_dist * r->ray_dir.x;
	r->wall_x -= floor(r->wall_x);
	r->tex.x = (int)(r->wall_x * (double)(d->wall[r->w].width));
	if (r->w == WE || r->w == SO)
		r->tex.x = d->wall[r->w].width - r->tex.x - 1;
	r->tex_step = 1.0 * d->wall[r->w].height / r->lineheight;
	r->tex_pos = (r->draw_start - MIHEIGHT + r->lineheight / 2) * r->tex_step;
}

void	draw(t_data *d, t_raycast *r, int x)
{
	int	y;

	y = 0;
	while (y < r->draw_start)
	{
		mlx_set_pixel(&d->i, x, y, d->c.c_color);
		y++;
	}
	while (y < r->draw_end)
	{
		r->tex.y = (int)r->tex_pos & (d->wall[r->w].height - 1);
		r->tex_pos += r->tex_step;
		r->color = d->wall[r->w].addr[d->wall[r->w].width
			* r->tex.y + r->tex.x];
		mlx_set_pixel(&d->i, x, y, r->color);
		y++;
	}
	while (y < HEIGHT)
	{
		mlx_set_pixel(&d->i, x, y, d->c.f_color);
		y++;
	}
}

void	raycasting(t_data *d, t_player *p, t_raycast *r)
{
	int	x;

	x = 0;
	while (++x < WIDTH)
	{
		r->camera_x = 2 * x / (double)WIDTH - 1;
		r->ray_dir.x = p->dir.x + p->plane.x * r->camera_x;
		r->ray_dir.y = p->dir.y + p->plane.y * r->camera_x;
		init_ray(p, r);
		perform_dda(d, r);
		calculate_draw_height(r);
		calculate_texture_coor(d, r, p);
		draw(d, r, x);
		x++;
	}
}
