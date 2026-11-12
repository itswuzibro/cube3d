/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_characters_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:48:32 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 15:51:55 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static void	init_wizard(t_data *d, t_enemy *wizard)
{
	wizard->ms = WIZARD_WMS;
	wizard->life = 150;
	wizard->damages = 50;
	wizard->attack_range = 8.0f;
	wizard->atk_interval = 1500;
	wizard->transform.scale.x = 0.8f;
	wizard->transform.scale.y = 0.8f;
	wizard->transform.add_y = 150;
	wizard->xp_gain = 282;
	set_flip_core(&wizard->idle, d->wizard_idle, 2, 8);
	set_flip_time(&wizard->idle, -1, 200, -1);
	set_flip_core(&wizard->walk, d->wizard_walk, 4, 8);
	set_flip_time(&wizard->walk, -1, 150, -1);
	set_flip_core(&wizard->run, d->wizard_walk, 4, 8);
	set_flip_time(&wizard->run, -1, 75, -1);
	set_flip_core(&wizard->attack, d->wizard_atk, 3, 1);
	set_flip_time(&wizard->attack, -1, 150, 2);
	set_flip_core(&wizard->death, d->wizard_death, 19, 1);
	set_flip_time(&wizard->death, 1, 150, -1);
	set_flip_core(&wizard->pain, d->wizard_pain, 1, 8);
	set_flip_time(&wizard->pain, -1, 500, -1);
}

static void	init_weredragon(t_data *d, t_enemy *weredragon)
{
	weredragon->ms = WEREDRAGON_WMS;
	weredragon->life = 250;
	weredragon->damages = 100;
	weredragon->attack_range = 1.0f;
	weredragon->atk_interval = 1500;
	weredragon->transform.scale.x = 1.0f;
	weredragon->transform.scale.y = 1.0f;
	weredragon->transform.add_y = 0.0f;
	weredragon->xp_gain = 328;
	set_flip_core(&weredragon->idle, d->weredragon_idle, 2, 8);
	set_flip_time(&weredragon->idle, -1, 270, -1);
	set_flip_core(&weredragon->walk, d->weredragon_walk, 6, 8);
	set_flip_time(&weredragon->walk, -1, 135, -1);
	set_flip_core(&weredragon->run, d->weredragon_walk, 6, 8);
	set_flip_time(&weredragon->run, -1, 70, -1);
	set_flip_core(&weredragon->attack, d->weredragon_attack, 2, 1);
	set_flip_time(&weredragon->attack, -1, 170, 1);
	set_flip_core(&weredragon->death, d->weredragon_death, 9, 1);
	set_flip_time(&weredragon->death, 1, 130, -1);
	set_flip_core(&weredragon->pain, d->weredragon_pain, 1, 8);
	set_flip_time(&weredragon->pain, -1, 300, -1);
}

static void	init_enemies(t_data *d)
{
	int	i;

	i = 0;
	while (i < MAX_E)
	{
		d->enemies[i].type = rand() % 2;
		d->enemies[i].active = true;
		d->enemies[i].pos = farthest_location(d);
		d->enemies[i].angle = rand() % 6;
		d->enemies[i].dir.x = cosf(d->enemies[i].angle);
		d->enemies[i].dir.y = sinf(d->enemies[i].angle);
		d->enemies[i].point_of_interest = d->enemies[i].pos;
		if (d->enemies[i].type == WIZARD)
			init_wizard(d, &d->enemies[i]);
		else if (d->enemies[i].type == WEREDRAGON)
			init_weredragon(d, &d->enemies[i]);
		d->enemies[i].state = ROAM;
		i++;
	}
}

static void	init_player(t_data *d)
{
	d->p.life = P_BASE_LIFE;
	d->p.life_max = P_BASE_LIFE;
	d->p.stamina = P_BASE_STAMINA;
	d->p.stamina_max = P_BASE_STAMINA;
	d->p.power_duration = P_BASE_POWER_DURATION;
	d->p.ms_powered = P_BASE_PMS;
	d->p.ms_sprint = P_BASE_RMS;
	d->p.ms_walk = P_BASE_WMS;
	d->p.damage = P_BASE_DAMAGE;
	d->p.nl_xp = 600;
	d->p.movespeed = d->p.ms_walk;
	d->p.rotspeed = PI;
	d->p.tired = false;
	d->p.dead = false;
	d->p.cooldown = 0;
	d->p.level = 1;
	set_flip_core(&d->p.attack, d->attack, 8, 1);
	set_flip_time(&d->p.attack, -1, P_BASE_ATK_INTERVAL, 5);
	set_flip_core(&d->p.interact, d->interact, 4, 1);
	set_flip_time(&d->p.interact, -1, 90, 3);
	set_flip_core(&d->p.idle, &d->player, 1, 1);
	set_flip_time(&d->p.idle, -1, -1, -1);
	set_flip_core(&d->p.nuke, d->player_nuke, 6, 1);
	set_flip_time(&d->p.nuke, -1, 250, 3);
}

void	init_characters(t_data *d)
{
	init_player(d);
	init_blood(d);
	init_enemies(d);
}
