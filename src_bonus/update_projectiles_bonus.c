/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_projectiles_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:27:27 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 15:28:30 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static void	move_projectile(t_data *d, t_projectile *proj, float delta_time)
{
	float	next_pos_x;
	float	next_pos_y;

	if (proj->angle < 0)
		proj->angle += 2 * PI;
	if (proj->angle > 2 * PI)
		proj->angle -= 2 * PI;
	proj->dir.x = cosf(proj->angle);
	proj->dir.y = sinf(proj->angle);
	next_pos_x = proj->pos.x + proj->dir.x * proj->ms * delta_time;
	next_pos_y = proj->pos.y + proj->dir.y * proj->ms * delta_time;
	if (!is_walkable(d, next_pos_x, next_pos_y, 0.15f))
		set_projectile_collided(proj);
	else
	{
		proj->pos.x = next_pos_x;
		proj->pos.y = next_pos_y;
	}
}

static void	manage_projectile_state(t_projectile *projectile)
{
	if (projectile->collided && projectile->current_anim->completed)
		projectile->active = false;
}

static void	draw_projectile(t_data *d, t_projectile *projectile)
{
	update_sprite_anim(d, projectile->current_anim,
		projectile->pos, projectile->angle);
	spritecasting(d, projectile->current_anim->frame,
		projectile->pos, projectile->transform);
}

void	update_projectiles(t_data *d, float delta_time)
{
	int	i;

	i = 0;
	while (i < MAX_P)
	{
		if (d->projectiles[i].active == true)
		{
			move_projectile(d, &d->projectiles[i], delta_time);
			if (d->projectiles[i].is_friendly)
				check_enemies_collision(d, &d->projectiles[i]);
			else
				check_player_collision(d, &d->projectiles[i]);
			check_projectiles_collisions(d, &d->projectiles[i]);
			draw_projectile(d, &d->projectiles[i]);
			manage_projectile_state(&d->projectiles[i]);
		}
		i++;
	}
}
