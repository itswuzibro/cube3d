/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_enemies_attacks_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:31:18 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 18:06:03 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static void	wizard_move(t_data *d, t_enemy *wizard, float delta_time)
{
	wizard->ms = WIZARD_RMS;
	wizard->current_anim = &wizard->walk;
	wizard->angle = find_angle_to_location(wizard->pos, d->p.pos);
	move_enemy(d, wizard, delta_time);
}

void	wizard_attack(t_data *d, t_enemy *wz, float delta_time)
{
	if (distance(d->p.pos, wz->pos) > wz->attack_range)
		wizard_move(d, wz, delta_time);
	else if (gettime() - wz->atk_timer > wz->atk_interval)
	{
		wz->current_anim = &wz->attack;
		if (wz->current_anim->event)
		{
			wz->angle = find_angle_to_location(wz->pos, d->p.pos);
			launch_projectile(d, wz->pos, wz->angle, false);
			wz->atk_timer = gettime();
		}
	}
	else
	{
		wz->current_anim = &wz->walk;
		if (distance(wz->point_of_interest, wz->pos) < 0.5f)
		{
			wz->point_of_interest = random_valid_location(d);
			wz->angle = find_angle_to_location(wz->pos, wz->point_of_interest);
		}
		move_enemy(d, wz, delta_time);
	}
}

static void	weredragon_run_away(t_data *d, t_enemy *weredragon, float dt)
{
	weredragon->current_anim = &weredragon->run;
	weredragon->ms = WEREDRAGON_RMS;
	weredragon->angle = find_angle_to_location(weredragon->pos, d->p.pos);
	move_enemy(d, weredragon, dt);
}

void	weredragon_attack(t_data *d, t_enemy *weredragon, float delta_time)
{
	bool		can_attack;
	bool		in_range;
	static bool	is_attacking = false;

	can_attack = gettime() - weredragon->atk_timer > weredragon->atk_interval;
	in_range = distance(d->p.pos, weredragon->pos) <= weredragon->attack_range;
	if ((can_attack && in_range) || is_attacking)
	{
		weredragon->current_anim = &weredragon->attack;
		if (is_attacking == false)
			is_attacking = true;
		if (weredragon->current_anim->event)
			apply_damage_on_player(d, &d->p, weredragon->damages);
		if (weredragon->current_anim->completed)
		{
			is_attacking = false;
			weredragon->atk_timer = gettime();
			weredragon->current_anim->is_durty = true;
		}
	}
	else if (!in_range)
		weredragon_run_away(d, weredragon, delta_time);
	else
		weredragon->current_anim = &weredragon->idle;
}
