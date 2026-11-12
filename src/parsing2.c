/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:07:00 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/17 17:25:49 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static bool	is_authorized(char c, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (c == s[i])
			return (true);
		i++;
	}
	return (false);
}

void	authorized_char(t_data *d)
{
	int	x;
	int	y;

	y = 0;
	while (d->c.map[y])
	{
		x = 0;
		while (d->c.map[y][x])
		{
			if (is_authorized(d->c.map[y][x], CHARSET) == false)
			{
				printf("unautorized: %c\n", d->c.map[y][x]);
				exit_and_free(d, MAP_ERROR);
			}
			x++;
		}
		y++;
	}
}
