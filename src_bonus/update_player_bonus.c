/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:29:10 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 17:45:28 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	power_timer(t_player *player)
{
	time_t	now;

	now = gettime();
	if (player->powered == true && now >= player->powerdown)
	{
		printf("stoped\n");
		player->powered = false;
		player->movespeed = player->ms_walk;
	}
}

void	rotate_player(t_data *d, t_player *player, float delta_time)
{
	float	rotvelocity;

	rotvelocity = player->rotspeed * delta_time;
	if (d->k.left_arrow)
		player->angle -= rotvelocity;
	if (d->k.right_arrow)
		player->angle += rotvelocity;
	if (player->angle < 0)
		player->angle += 2 * PI;
	if (player->angle > 2 * PI)
		player->angle -= 2 * PI;
	player->dir.x = cosf(player->angle);
	player->dir.y = sinf(player->angle);
	player->plane.x = -player->dir.y * 0.66;
	player->plane.y = player->dir.x * 0.66;
}

static void	move_player(t_data *d, t_player *player, float vel_x, float vel_y)
{
	t_fvector	next_pos;

	next_pos.x = player->pos.x + vel_x;
	next_pos.y = player->pos.y + vel_y;
	if (is_walkable(d, next_pos.x, player->pos.y, 0.1f))
		player->pos.x = next_pos.x;
	if (is_walkable(d, player->pos.x, next_pos.y, 0.1f))
		player->pos.y = next_pos.y;
}

void	update_player_state(t_data *d, t_player *player)
{
	if (player->state == ATTACK)
		player_state_attack(d, player);
	else if (player->state == INTERACT)
	{
		player->current_anim = &player->interact;
		if (player->interact.completed)
			player->state = PASSIVE;
		else if (player->interact.event)
			player_interact(d, player);
	}
	else if (player->state == NUKE)
	{
		player->current_anim = &player->nuke;
		if (player->current_anim->completed)
			player->state = PASSIVE;
		else if (player->current_anim->event)
			player_wipe(d, player);
	}
	else
		player->current_anim = &player->idle;
}

void	update_player(t_data *d, t_player *p, float dt)
{
	float	ms;

	(power_timer(p), rotate_player(d, p, dt));
	ms = p->movespeed;
	if (d->c.map[(int)p->pos.y][(int)p->pos.x] == '4')
		ms *= 0.5f;
	if (d->k.s == true)
		move_player(d, p, -p->dir.x * ms * dt, -p->dir.y * ms * dt);
	if (d->k.d == true)
		move_player(d, p, -p->dir.y * ms * dt, p->dir.x * ms * dt);
	if (d->k.q == true || d->k.a == true)
		move_player(d, p, p->dir.y * ms * dt, -p->dir.x * ms * dt);
	if (d->k.z == true || d->k.w == true)
		move_player(d, p, p->dir.x * ms * dt, p->dir.y * ms * dt);
	if (d->k.space == true)
		p->state = ATTACK;
	update_player_state(d, &d->p);
	p->actual_case = d->c.map[(int)p->pos.y][(int)p->pos.x];
	p->hands_offset.y = fabs(sin((p->pos.x + p->pos.y) * 2))
		* 30 + fabs(sin(d->time)) * 10;
	p->hands_offset.x = sin((p->pos.x + p->pos.y) * 2)
		* 30 + sin(d->time) * 10;
	update_flipbook(p->current_anim);
	draw_player(d, p);
}
