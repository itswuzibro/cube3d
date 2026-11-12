/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position_orientation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:13:07 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/17 17:32:18 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	determine_player_orientation(t_data *d, t_player *p, char c)
{
	if (c == 'N')
	{
		p->dir.x = 0;
		p->dir.y = -1;
		p->angle = 2 * PI * 0.75;
	}
	else if (c == 'S')
	{
		p->dir.x = 0;
		p->dir.y = 1;
		p->angle = 2 * PI * 0.25;
	}
	else if (c == 'W')
	{
		p->dir.x = -1;
		p->dir.y = 0;
		p->angle = 2 * PI * 0.50;
	}
	else if (c == 'E')
	{
		p->dir.x = 1;
		p->dir.y = 0;
		p->angle = 0;
	}
	rotate_player(d, d->delta_time);
}

void	determine_player_position(t_data *d)
{
	int			i;
	int			j;
	static int	count = 0;

	i = -1;
	while (d->c.map[++i])
	{
		j = -1;
		while (d->c.map[i][++j])
		{
			if (d->c.map[i][j] == '\n')
				d->c.map[i][j] = '\0';
			if (d->c.map[i][j] == 'N' || d->c.map[i][j] == 'S'
				|| d->c.map[i][j] == 'W' || d->c.map[i][j] == 'E' )
			{
				count++;
				d->p.pos.x = j + 0.5f;
				d->p.pos.y = i + 0.5f;
				determine_player_orientation(d, &d->p, d->c.map[i][j]);
				d->c.map[i][j] = '0';
			}
		}
	}
	if (count != 1)
		exit_and_free(d, PLAYER_ERR);
}
