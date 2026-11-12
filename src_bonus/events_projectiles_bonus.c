/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_projectiles_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:55:57 by injah             #+#    #+#             */
/*   Updated: 2025/09/19 15:43:31 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	reset_projectile(t_projectile *p, t_fvector pos, float angle, bool bro)
{
	p->active = true;
	p->angle = angle;
	p->dir.x = cosf(angle);
	p->dir.y = sinf(angle);
	p->pos.x = pos.x + p->dir.x * 0.2f;
	p->pos.y = pos.y + p->dir.y * 0.2f;
	p->ms = 10.0f;
	p->is_friendly = bro;
	p->collided = false;
	p->current_anim = &p->flip_launched;
	p->transform.scale.x = PRO_SCALE_X;
	p->transform.scale.y = PRO_SCALE_Y;
	p->transform.add_y = PRO_ADD_Y;
}

void	launch_projectile(t_data *d, t_fvector pos, float angle, bool is_friend)
{
	static int	i = 0;

	if (d->projectiles[i].active == false)
	{
		reset_projectile(&d->projectiles[i], pos, angle, is_friend);
		if (is_friend)
		{
			d->projectiles[i].flip_launched.imgs = d->projectile_player;
			d->projectiles[i].flip_explode.imgs = d->projectile_player;
			d->projectiles[i].damages = d->p.damage;
		}
		else
		{
			d->projectiles[i].flip_launched.imgs = d->projectile_wizard;
			d->projectiles[i].flip_explode.imgs = d->projectile_wizard;
			d->projectiles[i].damages = 30;
		}
	}
	i++;
	i %= MAX_P;
}

void	set_projectile_collided(t_projectile *projectile)
{
	if (projectile->collided == false)
	{
		projectile->collided = true;
		projectile->ms = 0;
		projectile->current_anim = &projectile->flip_explode;
		projectile->transform.scale.x *= 3;
		projectile->transform.scale.y *= 3;
	}
}
