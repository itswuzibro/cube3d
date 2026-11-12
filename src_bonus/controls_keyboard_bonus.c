/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_keyboard_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:29:28 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 13:26:02 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static void	keys_pressed(int key, t_data *d)
{
	if (key == 'z' || key == 'w')
	{
		d->k.z = true;
		d->k.w = true;
	}
	if (key == 's')
		d->k.s = true;
	if (key == 'd')
		d->k.d = true;
	if (key == 'q' || key == 'a')
	{
		d->k.q = true;
		d->k.a = true;
	}
	if (key == 'e')
		d->p.state = INTERACT;
	if (key == 'f' && d->p.powered)
		d->p.state = NUKE;
	if (key == 'm')
		d->k.m = true;
	if (key == 'p')
		d->game_state = PAUSE;
	if (key == ' ')
		d->k.space = true;
}

static void	keys_released(int key, t_data *d)
{
	if (key == 'z' || key == 'w')
	{
		d->k.z = false;
		d->k.w = false;
	}
	if (key == 's')
		d->k.s = false;
	if (key == 'd')
		d->k.d = false;
	if (key == 'q' || key == 'a')
	{
		d->k.q = false;
		d->k.a = false;
	}
	if (key == ' ')
		d->k.space = false;
	if (key == 'm')
		d->k.m = false;
}

int	control_pressed(int key, t_data *d)
{
	keys_pressed(key, d);
	if (key == UP_ARROW)
		d->k.up_arrow = true;
	if (key == DOWN_ARROW)
		d->k.down_arrow = true;
	if (key == LEFT_ARROW)
		d->k.left_arrow = true;
	if (key == RIGHT_ARROW)
		d->k.right_arrow = true;
	if (key == ENTER)
		d->k.enter = true;
	if (key == MAJ)
		d->k.maj = true;
	if (key == ECHAP)
		exit_and_free(d, "Closing game...\n");
	return (0);
}

int	control_released(int key, t_data *d)
{
	keys_released(key, d);
	if (key == UP_ARROW)
		d->k.up_arrow = false;
	if (key == DOWN_ARROW)
		d->k.down_arrow = false;
	if (key == LEFT_ARROW)
		d->k.left_arrow = false;
	if (key == RIGHT_ARROW)
		d->k.right_arrow = false;
	if (key == ENTER)
		d->k.enter = false;
	if (key == MAJ)
		d->k.maj = false;
	return (0);
}
