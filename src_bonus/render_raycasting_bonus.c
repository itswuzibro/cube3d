/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycasting_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:36:21 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 16:54:28 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static void	determine_raycast_and_update_distances(t_raycast *r)
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
}

void	perform_dda(t_data *d, t_raycast *r)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		determine_raycast_and_update_distances(r);
		if (is_out_of_map(d->c.cols, d->c.rows, r->map_x, r->map_y))
		{
			hit = 1;
			r->letter = CASE_WALL;
		}
		else if (is_blocking_ray(d->c.map, r->map_x, r->map_y))
		{
			hit = 1;
			r->letter = d->c.map[r->map_y][r->map_x];
		}
	}
}

void	calculate_wall_size(t_raycast *r)
{
	if (r->side == 0)
		r->perp_wall_dist = (r->side_dist.x - r->delta_dist.x);
	else
		r->perp_wall_dist = (r->side_dist.y - r->delta_dist.y);
	r->lineheight = (int)((HEIGHT / r->perp_wall_dist));
	r->draw_start = MIHEIGHT - r->lineheight / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = MIHEIGHT + r->lineheight / 2;
	if (r->draw_end > HEIGHT - 1)
		r->draw_end = HEIGHT - 1;
}

void	calculate_texture_coor(t_raycast *r, t_player *p)
{
	if (r->side == 0)
		r->wall_x = p->pos.y + r->perp_wall_dist * r->ray_dir.y;
	else
		r->wall_x = p->pos.x + r->perp_wall_dist * r->ray_dir.x;
	r->wall_x -= floor(r->wall_x);
	r->tex.x = (int)(r->wall_x * (double)(r->selected_img->width));
	if (r->w == WE || r->w == SO)
		r->tex.x = r->selected_img->width - r->tex.x - 1;
	r->tex_step = 1.0 * r->selected_img->height / r->lineheight;
	r->tex_pos = (r->draw_start - MIHEIGHT + r->lineheight / 2) * r->tex_step;
}

void	raycasting(t_data *d, t_player *p, t_raycast *r)
{
	int	x;

	x = 0;
	ft_memset(d->z_buffer, 100.0f, sizeof(float) * HEIGHT * WIDTH);
	while (x < WIDTH)
	{
		r->camera_x = 2 * x / (double)WIDTH - 1;
		r->door = false;
		r->ray_dir.x = p->dir.x + p->plane.x * r->camera_x;
		r->ray_dir.y = p->dir.y + p->plane.y * r->camera_x;
		init_ray(p, r);
		perform_dda(d, r);
		select_img_by_letter(d, r);
		calculate_wall_size(r);
		calculate_texture_coor(r, p);
		draw(d, r, x);
		x++;
	}
	floorcasting(d);
}
