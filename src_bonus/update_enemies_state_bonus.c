/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_enemies_state_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 18:06:36 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 18:11:48 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	enemy_roaming(t_data *d, t_enemy *enemy, float delta_time)
{
	enemy->current_anim = &enemy->walk;
	move_enemy(d, enemy, delta_time);
	if (can_see_player(d, enemy->pos, enemy->angle, 15)
		|| can_see_player(d, enemy->pos, enemy->angle - PI / 4, 10)
		|| can_see_player(d, enemy->pos, enemy->angle + PI / 4, 10))
		enemy_change_state(enemy, ATTACK);
}

void	enemy_attack(t_data *d, t_enemy *enemy, float delta_time)
{
	if (enemy->type == WIZARD)
		wizard_attack(d, enemy, delta_time);
	else if (enemy->type == WEREDRAGON)
		weredragon_attack(d, enemy, delta_time);
}

void	enemy_passive(t_data *d, t_enemy *enemy)
{
	enemy->current_anim = &enemy->idle;
	if (can_see_player(d, enemy->pos, enemy->angle, 15)
		|| can_see_player(d, enemy->pos, enemy->angle - PI / 4, 10)
		|| can_see_player(d, enemy->pos, enemy->angle + PI / 4, 10))
		enemy_change_state(enemy, ATTACK);
}
