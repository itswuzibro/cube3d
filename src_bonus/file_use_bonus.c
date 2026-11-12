/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_use_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:13:07 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 20:19:03 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

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
	rotate_player(d, &d->p, d->delta_time);
}

static void	determine_player_position(t_data *d)
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
				d->c.map[i][j] = CASE_FLOOR;
			}
		}
	}
	if (count != 1)
		exit_and_free(d, PLAYER_ERR);
}

static void	format_map(t_data *d)
{
	char	**new;
	int		i;
	int		j;

	i = -1;
	new = malloc(sizeof(char *) * (d->c.rows + 1));
	if (!new)
		exit_and_free(d, ALLOC_ERROR);
	while (++i < d->c.rows)
	{
		new[i] = malloc(sizeof(char) * (d->c.cols + 1));
		if (!new[i])
			exit_and_free(d, ALLOC_ERROR);
		ft_memset(new[i], '1', d->c.cols);
		j = -1;
		while (d->c.map[i][++j])
		{
			if (d->c.map[i][j] != ' ')
				new[i][j] = d->c.map[i][j];
		}
		new[i][d->c.cols] = '\0';
	}
	new[i] = NULL;
	ft_free_tab(d->c.map);
	d->c.map = new;
}

void	file_use(t_data *d)
{
	format_map(d);
	authorized_char(d);
	determine_player_position(d);
}
