/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_collisions_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:27:05 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 17:27:49 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	check_enemies_collision(t_data *d, t_projectile *projectile)
{
	int	i;

	i = 0;
	while (i < MAX_E)
	{
		if (d->enemies[i].state != DEAD && projectile->collided == false)
		{
			if (distance(projectile->pos, d->enemies[i].pos) < 0.3f)
			{
				if (projectile->collided == false)
					set_projectile_collided(projectile);
				apply_damage_on_enemy(d, &d->enemies[i], projectile->damages);
				break ;
			}
		}
		i++;
	}
}

void	check_projectiles_collisions(t_data *d, t_projectile *projectile)
{
	int	i;

	i = 0;
	while (i < MAX_P)
	{
		if (d->projectiles[i].active && !d->projectiles[i].collided
			&& d->projectiles[i].is_friendly != projectile->is_friendly
			&& projectile->collided == false)
		{
			if (distance(projectile->pos, d->projectiles[i].pos) < 0.3f)
			{
				if (projectile->collided == false)
				{
					set_projectile_collided(projectile);
					set_projectile_collided(&d->projectiles[i]);
					projectile->transform.scale.x *= 2;
					d->projectiles[i].transform.scale.y *= 2;
				}
				break ;
			}
		}
		i++;
	}
}

void	check_player_collision(t_data *d, t_projectile *projectile)
{
	if (projectile->collided == false)
	{
		if (distance(projectile->pos, d->p.pos) < 0.3f)
		{
			set_projectile_collided(projectile);
			apply_damage_on_player(d, &d->p, projectile->damages);
		}
	}
}
