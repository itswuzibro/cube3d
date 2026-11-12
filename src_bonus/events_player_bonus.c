/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_player_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 03:14:43 by injah             #+#    #+#             */
/*   Updated: 2025/09/19 18:56:00 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	apply_damage_on_player(t_data *d, t_player *p, int damage)
{
	int	i;
	int	blood_count;

	blood_count = damage / 5;
	p->life -= damage;
	if (p->life <= 0)
	{
		d->ending_start = gettime();
		d->game_state = END;
	}
	i = -1;
	while (++i < MAX_BLOOD && blood_count)
	{
		if (p->blood[i].active == false)
		{
			p->blood[i].active = true;
			p->blood[i].pos.x = rand() % WIDTH - p->blood[i].img->width / 2;
			p->blood[i].pos.y = rand() % HEIGHT - p->blood[i].img->height / 2;
			p->blood[i].timer = gettime();
			p->blood[i].vel_y = 0;
			p->blood[i].interval = 1000;
			blood_count--;
		}
	}
	d->screen_shake = damage / 2;
}

void	player_interact(t_data *d, t_player *player)
{
	char		front_case_char;
	t_ivector	front_case;

	front_case.x = player->pos.x + player->dir.x;
	front_case.y = player->pos.y + player->dir.y;
	front_case_char = '\0';
	if (!is_out_of_map(d->c.cols, d->c.rows, front_case.x, front_case.y))
		front_case_char = d->c.map[front_case.y][front_case.x];
	if (front_case_char == CASE_CDOOR)
		d->c.map[front_case.y][front_case.x] = CASE_ODOOR;
	else if (front_case_char == CASE_ODOOR)
		d->c.map[front_case.y][front_case.x] = CASE_CDOOR;
}

void	player_power(t_player *player)
{
	player->powered = true;
	player->movespeed = player->ms_powered;
	player->powerdown = gettime() + player->power_duration;
}

void	player_wipe(t_data *d, t_player *player)
{
	int	i;

	i = 0;
	while (i < MAX_E)
	{
		if (distance(player->pos, d->enemies[i].pos) < 10.0f)
			apply_damage_on_enemy(d, &d->enemies[i], 1000);
		i++;
	}
	player->powered = false;
}

void	player_xp(t_player *player, int xp)
{
	player->xp += xp;
	if (player->xp >= player->nl_xp)
	{
		player->level++;
		player->nl_xp += 500 + player->level * 100;
		player->life_max += P_LEVEL_LIFE;
		player->life = player->life_max;
		player->stamina_max += P_LEVEL_STAMINA;
		player->stamina = player->stamina_max;
		player->damage += P_LEVEL_DAMAGE;
		player->power_duration += P_LEVEL_POWER_DURATION;
		player->attack.interval -= P_LEVEL_ATK_INTERVAL;
	}
}
