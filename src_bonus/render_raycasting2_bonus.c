/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycasting2_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:26:48 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 17:17:28 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	select_img_by_letter(t_data *d, t_raycast *r)
{
	if (r->side == 0 && r->ray_dir.x > 0)
		r->w = EA;
	else if (r->side == 0 && r->ray_dir.x <= 0)
		r->w = WE;
	else if (r->side == 1 && r->ray_dir.y < 0)
		r->w = NO;
	else
		r->w = SO;
	if (r->letter == CASE_CDOOR)
		r->selected_img = &d->door[0];
	else if (r->letter == CASE_ODOOR)
		r->selected_img = &d->door[1];
	else if (r->letter == CASE_WALL)
		r->selected_img = &d->wall[r->w];
	else if (r->letter == CASE_WINE)
		r->selected_img = &d->wine;
}

unsigned int	calculate_coor_get_txtr_color(t_raycast *r, unsigned int color)
{
	r->tex.y = (int)r->tex_pos & (r->selected_img->height - 1);
	r->tex_pos += r->tex_step;
	color = r->selected_img->addr[r->selected_img->width * r->tex.y + r->tex.x];
	return (color);
}

static unsigned int	depth_and_light(t_data *d, unsigned int color, int x, int y)
{
	if (d->light == false)
		color = (color >> 1) & 0x7f7f7f;
	if (d->r.w == NO || d->r.w == SO)
		color = (color >> 1) & 0x7f7f7f;
	mlx_set_pixel(&d->i, x, y, color);
	d->z_buffer[y * WIDTH + x] = d->r.perp_wall_dist;
	return (color);
}

static void	recall_raycast(t_data *d, t_raycast *r, int x)
{
	perform_dda(d, r);
	select_img_by_letter(d, r);
	calculate_wall_size(r);
	calculate_texture_coor(r, &d->p);
	draw(d, r, x);
}

void	draw(t_data *d, t_raycast *r, int x)
{
	int				y;
	unsigned int	color;

	y = 0;
	d->transparent = 0;
	color = d->c.c_color;
	if (d->light == false)
		color = (color >> 1) & 0x7f7f7f;
	while (y < r->draw_start)
	{
		mlx_set_pixel(&d->i, x, y, color);
		d->z_buffer[y * WIDTH + x] = 10000;
		y++;
	}
	while (y < r->draw_end)
	{
		color = calculate_coor_get_txtr_color(r, color);
		if (color == 0xFF000000)
			d->transparent = 1;
		else if (r->perp_wall_dist <= d->z_buffer[y * WIDTH + x])
			color = depth_and_light(d, color, x, y);
		y++;
	}
	if (d->transparent)
		return (recall_raycast(d, r, x));
}
