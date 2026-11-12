/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player_state_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:36:03 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 17:45:36 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	player_state_attack(t_data *d, t_player *player)
{
	if (player->current_anim != &player->attack)
		reset_flip(&player->attack);
	player->current_anim = &player->attack;
	if (player->current_anim->completed)
	{
		player->state = PASSIVE;
		player->current_anim = &player->idle;
	}
	else if (player->attack.event)
		launch_projectile(d, player->pos, player->angle, true);
}

void	draw_player(t_data *d, t_player *p)
{
	copypaste_img(p->current_anim->frame, &d->i, p->hands_offset.x,
		HEIGHT - d->status[0].height
		- p->current_anim->frame->height + p->hands_offset.y + 30);
}
