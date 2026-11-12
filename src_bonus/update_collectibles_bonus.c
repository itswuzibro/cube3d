/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_collectibles_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:33:40 by injah             #+#    #+#             */
/*   Updated: 2025/09/19 18:55:17 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static void	perk_given_by_collectible(t_data *d, int i)
{
	if (distance(d->p.pos, d->col[i].pos) < 0.5f)
	{
		player_xp(&d->p, d->col[i].xp_gain);
		d->p.life += d->col[i].life_gain;
		if (d->p.life > d->p.life_max)
			d->p.life = d->p.life_max;
		d->p.stamina += d->col[i].stamina_gain;
		if (d->p.stamina > d->p.stamina_max)
			d->p.stamina = d->p.stamina_max;
		d->col[i].active = false;
	}
}

void	update_collectibles(t_data *d, float deltatime)
{
	int	i;

	i = -1;
	while (++i < MAX_C)
	{
		if (d->col[i].active)
		{
			d->col[i].transform.add_y += d->col[i].vel_y * deltatime;
			if (d->col[i].transform.add_y > 100)
			{
				d->col[i].transform.add_y = 100;
				d->col[i].vel_y = -200;
			}
			if (d->col[i].transform.add_y < -50)
			{
				d->col[i].transform.add_y = -50;
				d->col[i].vel_y = 200;
			}
			update_sprite_anim(d, &d->col[i].flip,
				d->col[i].pos, d->col[i].angle);
			spritecasting(d, d->col[i].flip.frame,
				d->col[i].pos, d->col[i].transform);
			perk_given_by_collectible(d, i);
		}
	}
}
