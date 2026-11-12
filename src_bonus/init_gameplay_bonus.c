/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gameplay_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:45:47 by injah             #+#    #+#             */
/*   Updated: 2025/09/19 15:58:33 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static void	init_weather(t_data *d)
{
	int	i;

	i = 0;
	d->light = false;
	d->menu_light = false;
	d->last_lightning = gettime();
	d->n_lightning = 0;
	d->l_duration = 0;
	while (i < RAIN_C)
	{
		d->rain[i].pos_x = rand() % WIDTH;
		d->rain[i].pos_y = rand() % HEIGHT;
		d->rain[i].dir_x = sin(rand()) / 2.5;
		d->rain[i].dir_y = 1;
		d->rain[i].len = (rand() % 20) + 5;
		d->rain[i].speed = (rand() % d->rain[i].len + 1) * 100 + 500;
		i++;
	}
}

static void	init_projectiles(t_data *d)
{
	int	i;

	i = 0;
	while (i < MAX_P)
	{
		d->projectiles[i].pos.x = 3;
		d->projectiles[i].pos.y = 3;
		d->projectiles[i].dir.x = 0;
		d->projectiles[i].dir.y = 0;
		d->projectiles[i].ms = 0;
		d->projectiles[i].damages = 30;
		set_flip_core(&d->projectiles[i].flip_launched,
			d->projectile_player, 3, 1);
		set_flip_time(&d->projectiles[i].flip_launched, -1, 100, -1);
		set_flip_core(&d->projectiles[i].flip_explode,
			d->projectile_player, 4, 1);
		set_flip_time(&d->projectiles[i].flip_explode, -1, 50, -1);
		d->projectiles[i].is_friendly = false;
		d->projectiles[i].collided = false;
		d->projectiles[i].active = false;
		d->projectiles[i].transform.scale.x = PRO_SCALE_X;
		d->projectiles[i].transform.scale.y = PRO_SCALE_Y;
		d->projectiles[i].transform.add_y = PRO_ADD_Y;
		i++;
	}
}

void	init_collectibles(t_data *d)
{
	int	i;

	i = 0;
	while (i < MAX_C)
	{
		d->col[i].pos = random_valid_location(d);
		d->col[i].angle = rand() % 7;
		d->col[i].life_gain = 20;
		d->col[i].stamina_gain = 3;
		d->col[i].xp_gain = 112;
		d->col[i].transform.scale.x = 0.3f;
		d->col[i].transform.scale.y = 0.3f;
		d->col[i].transform.add_y = 0;
		d->col[i].vel_y = 303;
		set_flip_core(&d->col[i].flip, d->skull, 1, 18);
		set_flip_time(&d->col[i].flip, -1, -1, -1);
		d->col[i].active = true;
		i++;
	}
}

void	init_portal(t_data *d)
{
	d->portal.pos = farthest_location(d);
	set_flip_core(&d->portal.close, d->portal_close, 8, 1);
	set_flip_time(&d->portal.close, -1, 100, -1);
	set_flip_core(&d->portal.ascending, d->portal_ascending, 3, 1);
	set_flip_time(&d->portal.ascending, 1, 200, -1);
	set_flip_core(&d->portal.descending, d->portal_descending, 3, 1);
	set_flip_time(&d->portal.descending, 1, 200, -1);
	set_flip_core(&d->portal.far, d->portal_far, 8, 1);
	set_flip_time(&d->portal.far, -1, 100, -1);
	d->portal.current_anim = &d->portal.far;
	d->portal.transform.scale.x = 1.0f;
	d->portal.transform.scale.y = 1.0f;
}

void	init_gameplay(t_data *d)
{
	init_characters(d);
	init_weather(d);
	init_projectiles(d);
	init_collectibles(d);
	init_portal(d);
}
