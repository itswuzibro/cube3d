/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_vector_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:26:28 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 17:26:29 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

float	distance(t_fvector pos_a, t_fvector pos_b)
{
	float	delta_x;
	float	delta_y;

	delta_x = pos_a.x - pos_b.x;
	delta_y = pos_a.y - pos_b.y;
	return (sqrtf(delta_x * delta_x + delta_y * delta_y));
}

float	find_angle_to_location(t_fvector start, t_fvector target)
{
	float	dx;
	float	dy;
	float	angle;

	dx = target.x - start.x;
	dy = target.y - start.y;
	angle = atan2f(dy, dx);
	return (angle);
}

t_fvector	random_valid_location(t_data *d)
{
	t_fvector	location;

	location.x = rand() % d->c.cols + (float)(20 + rand() % 60) / 100;
	location.y = rand() % d->c.rows + (float)(20 + rand() % 60) / 100;
	while (!is_floor(d->c.map, location.x, location.y))
	{
		location.x = rand() % d->c.cols + 0.5f;
		location.y = rand() % d->c.rows + 0.5f;
	}
	return (location);
}

t_fvector	farthest_location(t_data *d)
{
	t_fvector	valid_pos[2];
	t_fvector	farthest;
	int			i;

	i = 0;
	farthest = random_valid_location(d);
	while (i < 2)
	{
		valid_pos[i] = random_valid_location(d);
		i++;
	}
	i = 0;
	while (i < 2)
	{
		if (distance(valid_pos[i], d->p.pos) > distance(farthest, d->p.pos))
			farthest = valid_pos[i];
		i++;
	}
	return (farthest);
}

t_ivector	make_ivector(int x, int y)
{
	t_ivector	ivector;

	ivector.x = x;
	ivector.y = y;
	return (ivector);
}
