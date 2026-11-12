/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_spritecasting_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:58:41 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 16:00:20 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

bool	init_scasting(t_data *d, t_scast *s, t_fvector *pos, t_transform *t)
{
	s->sprite_rel_x = pos->x - d->p.pos.x;
	s->sprite_rel_y = pos->y - d->p.pos.y;
	s->inv_det = 1.0 / (d->p.plane.x * d->p.dir.y - d->p.dir.x * d->p.plane.y);
	s->transform_x = s->inv_det
		* (d->p.dir.y * s->sprite_rel_x - d->p.dir.x * s->sprite_rel_y);
	s->transform_y = s->inv_det
		* (-d->p.plane.y * s->sprite_rel_x + d->p.plane.x * s->sprite_rel_y);
	if (s->transform_y <= 0.01 || isnan(s->transform_y)
		|| isinf(s->transform_y))
		return (true);
	s->screen_x = (int)(MIWIDTH * (1 + s->transform_x / s->transform_y));
	s->vmove_screen = (int)(t->add_y / s->transform_y);
	s->sprite_h = (int)(HEIGHT / s->transform_y) * t->scale.x;
	s->sprite_w = (int)(HEIGHT / s->transform_y) * t->scale.y;
	if (s->sprite_h <= 0 || s->sprite_w <= 0)
		return (true);
	return (false);
}
