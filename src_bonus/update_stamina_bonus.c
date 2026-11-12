/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_stamina_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:23:10 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 15:23:11 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static void	setup_sprinting(t_player *player, float delta_time)
{
	player->movespeed = player->ms_sprint;
	player->stamina -= 2 * delta_time;
	if (player->stamina < 0)
		player->stamina = 0;
}

void	update_stamina(t_data *d, t_player *player, float delta_time)
{
	time_t	time;

	if (player->powered == true)
		return ;
	time = gettime();
	if (d->k.maj == true && player->stamina > 0 && player->tired == false)
		setup_sprinting(player, delta_time);
	else if (d->k.maj == false && player->tired == false)
	{
		player->movespeed = player->ms_walk;
		player->stamina += 4 * delta_time;
		if (player->stamina > player->stamina_max)
			player->stamina = player->stamina_max;
	}
	if (player->stamina <= 0 && player->tired == false)
	{
		player->tired = true;
		player->cooldown = time + 3500;
		player->movespeed = 0.5f;
	}
	if (player->tired && time >= player->cooldown)
		player->tired = false;
}
