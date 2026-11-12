/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_enemies_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 19:40:44 by injah             #+#    #+#             */
/*   Updated: 2025/09/19 18:11:09 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	move_enemy(t_data *d, t_enemy *en, float delta_time)
{
	t_fvector	next_pos;
	bool		collide;

	collide = false;
	next_pos = en->pos;
	en->dir.x = cosf(en->angle);
	en->dir.y = sinf(en->angle);
	next_pos.x = en->pos.x + en->dir.x * delta_time * en->ms;
	next_pos.y = en->pos.y + en->dir.y * delta_time * en->ms;
	if (is_walkable(d, next_pos.x, en->pos.y, 0.2f))
		en->pos.x = next_pos.x;
	else
		collide = true;
	if (is_walkable(d, en->pos.x, next_pos.y, 0.2f))
		en->pos.y = next_pos.y;
	else
		collide = true;
	if (en->state == ROAM && collide)
	{
		en->point_of_interest = random_valid_location(d);
		en->angle = find_angle_to_location(en->pos, en->point_of_interest);
	}
}

static void	draw_enemy(t_data *d, t_enemy *enemy)
{
	update_sprite_anim(d, enemy->current_anim, enemy->pos, enemy->angle);
	spritecasting(d, enemy->current_anim->frame, enemy->pos, enemy->transform);
}

void	common_update(t_data *d, t_enemy *enemy, float delta_time)
{
	int	kill_count;

	kill_count = 0;
	if (enemy->state == DEAD)
	{
		enemy->current_anim = &enemy->death;
		kill_count++;
		return ;
	}
	else if (enemy->state == ROAM)
		enemy_roaming(d, enemy, delta_time);
	else if (enemy->state == ATTACK)
		enemy_attack(d, enemy, delta_time);
	else if (enemy->state == PASSIVE)
		enemy_passive(d, enemy);
	else if (enemy->state == PAIN)
	{
		enemy->current_anim = &enemy->pain;
		if (enemy->current_anim->completed)
			enemy->state = ATTACK;
	}
}

void	update_enemies(t_data *d, float delta_time)
{
	int	i;

	i = 0;
	while (i < MAX_E)
	{
		if (d->enemies[i].active)
		{
			common_update(d, &d->enemies[i], delta_time);
			draw_enemy(d, &d->enemies[i]);
		}
		i++;
	}
}
