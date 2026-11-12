/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_enemies_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:17:33 by injah             #+#    #+#             */
/*   Updated: 2025/09/19 18:16:13 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	enemy_change_state(t_enemy *enemy, t_state state)
{
	if (enemy->state == state)
		return ;
	enemy->state = state;
	if (state == PASSIVE)
		reset_flip(&enemy->idle);
	else if (state == ATTACK)
		reset_flip(&enemy->attack);
	else if (state == ROAM)
		reset_flip(&enemy->walk);
	else if (state == PAIN)
		reset_flip(&enemy->pain);
}

void	apply_damage_on_enemy(t_data *d, t_enemy *enemy, int damage)
{
	if (enemy->state != DEAD)
	{
		enemy->life -= damage;
		if (enemy->life <= 0)
		{
			player_xp(&d->p, enemy->xp_gain);
			d->p.kill_count++;
			if (d->p.kill_count % 5 == 0 && d->p.powered == false)
				player_power(&d->p);
			enemy->state = DEAD;
		}
		else
		{
			enemy->state = PAIN;
			reset_flip(&enemy->pain);
		}
	}
}

bool	can_see_player(t_data *d, t_fvector start, float angle, int view_max)
{
	int			i;
	t_fvector	see_pos;
	t_fvector	see_dir;

	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	see_dir.x = cosf(angle);
	see_dir.y = sinf(angle);
	i = 0;
	while (i < view_max)
	{
		see_pos.x = start.x + see_dir.x * i;
		see_pos.y = start.y + see_dir.y * i;
		if (is_out_of_map(d->c.cols, d->c.rows, see_pos.x, see_pos.y))
			return (false);
		if (is_wall(d->c.map, see_pos.x, see_pos.y))
			return (false);
		if (distance(see_pos, d->p.pos) < 1.0f)
			return (true);
		i++;
	}
	return (false);
}
