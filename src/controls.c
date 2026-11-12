/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:29:28 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/04 20:14:08 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	arrow_keys_pressed(int key, t_data *d)
{
	if (key == UP_ARROW)
		d->k.up_arrow = true;
	if (key == DOWN_ARROW)
		d->k.down_arrow = true;
	if (key == LEFT_ARROW)
		d->k.left_arrow = true;
	if (key == RIGHT_ARROW)
		d->k.right_arrow = true;
}

static void	arrow_keys_released(int key, t_data *d)
{
	if (key == UP_ARROW)
		d->k.up_arrow = false;
	if (key == DOWN_ARROW)
		d->k.down_arrow = false;
	if (key == LEFT_ARROW)
		d->k.left_arrow = false;
	if (key == RIGHT_ARROW)
		d->k.right_arrow = false;
}

int	control_pressed(int key, t_data *d)
{
	arrow_keys_pressed(key, d);
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
	if (key == 'm')
		d->k.m = true;
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
	arrow_keys_released(key, d);
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
	if (key == ENTER)
		d->k.enter = false;
	if (key == 'm')
		d->k.m = false;
	if (key == MAJ)
		d->k.maj = false;
	return (0);
}
