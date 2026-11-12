/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:29:10 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/17 17:32:44 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	rotate_player(t_data *d, float delta_time)
{
	float	rotvelocity;

	rotvelocity = d->p.rotspeed * delta_time;
	if (d->k.left_arrow)
		d->p.angle += -rotvelocity;
	if (d->k.right_arrow)
		d->p.angle += rotvelocity;
	if (d->p.angle < 0)
		d->p.angle += 2 * PI;
	if (d->p.angle > 2 * PI)
		d->p.angle -= 2 * PI;
	d->p.dir.x = cosf(d->p.angle);
	d->p.dir.y = sinf(d->p.angle);
	d->p.plane.x = -d->p.dir.y * 0.66;
	d->p.plane.y = d->p.dir.x * 0.66;
}

static void	move_up(t_data *d, float delta_time)
{
	if (d->k.z == true || d->k.w == true)
	{
		if (d->k.maj == true)
		{
			d->p.pos.x += d->p.dir.x * (d->p.movespeed + 1) * delta_time;
			d->p.pos.y += d->p.dir.y * d->p.movespeed * delta_time;
		}
		else
		{
			d->p.pos.x += d->p.dir.x * d->p.movespeed * delta_time;
			d->p.pos.y += d->p.dir.y * d->p.movespeed * delta_time;
		}
	}
}

static void	move_left(t_data *d, float delta_time)
{
	if (d->k.q == true || d->k.a == true)
	{
		d->p.pos.x += d->p.dir.y * d->p.movespeed * delta_time;
		d->p.pos.y += -d->p.dir.x * d->p.movespeed * delta_time;
	}
}

static void	move_down(t_data *d, float delta_time)
{
	if (d->k.s == true)
	{
		d->p.pos.x += -d->p.dir.x * d->p.movespeed * delta_time;
		d->p.pos.y += -d->p.dir.y * d->p.movespeed * delta_time;
	}
}

void	update_player(t_data *d, float delta_time)
{
	float			old_pos_x;
	float			old_pos_y;
	static float	time = 0;

	old_pos_x = d->p.pos.x;
	old_pos_y = d->p.pos.y;
	time += d->delta_time;
	move_up(d, delta_time);
	move_left(d, delta_time);
	move_down(d, delta_time);
	if (d->k.d == true)
	{
		d->p.pos.x += -d->p.dir.y * d->p.movespeed * delta_time;
		d->p.pos.y += d->p.dir.x * d->p.movespeed * delta_time;
	}
	if (d->c.map[(int)d->p.pos.y][(int)d->p.pos.x] == '1')
	{
		d->p.pos.x = old_pos_x;
		d->p.pos.y = old_pos_y;
	}
	d->p.hands_offset = fabs(sin(d->p.pos.x + d->p.pos.y)) * 50
		+ fabs(sin(time)) * 10;
	rotate_player(d, delta_time);
}
