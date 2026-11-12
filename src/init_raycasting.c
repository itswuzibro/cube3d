/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:36:09 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/17 17:37:36 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_ray(t_player *p, t_raycast *r)
{
	r->map_x = (int)(p->pos.x);
	r->map_y = (int)(p->pos.y);
	r->delta_dist.x = fabs(1 / r->ray_dir.x);
	r->delta_dist.y = fabs(1 / r->ray_dir.y);
	if (r->ray_dir.x < 0)
	{
		r->step.x = -1;
		r->side_dist.x = (p->pos.x - r->map_x) * r->delta_dist.x;
	}
	else
	{
		r->step.x = 1;
		r->side_dist.x = (r->map_x + 1.0 - p->pos.x) * r->delta_dist.x;
	}
	if (r->ray_dir.y < 0)
	{
		r->step.y = -1;
		r->side_dist.y = (p->pos.y - r->map_y) * r->delta_dist.y;
	}
	else
	{
		r->step.y = 1;
		r->side_dist.y = (r->map_y + 1.0 - p->pos.y) * r->delta_dist.y;
	}
}
