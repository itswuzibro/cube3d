/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:36:14 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 20:16:37 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	verif(t_data *d)
{
	int	i;

	i = 0;
	while (d->c.map[i])
	{
		ft_printf("|%s|\n", d->c.map[i]);
		i++;
	}
	ft_printf("\nno: |%s|\n", d->c.no);
	ft_printf("so: |%s|\n", d->c.so);
	ft_printf("ea: |%s|\n", d->c.ea);
	ft_printf("we: |%s|\n", d->c.we);
	ft_printf("f: |%s|\n", d->c.f);
	ft_printf("c: |%s|\n", d->c.c);
	ft_printf("cols: |%d|\n", d->c.cols);
	ft_printf("rows: |%d|\n\n", d->c.rows);
	i = 0;
	while (d->c.to_flood[i])
	{
		ft_printf("|%s|\n", d->c.to_flood[i]);
		i++;
	}
}

void	validate_map_format(t_data *d, char *s)
{
	int	i;

	i = 0;
	if (ft_strlen(s) < 3)
		exit_and_free(d, FORMAT_ERROR);
	while (s[i])
		i++;
	i--;
	if (s[i] != 'b' || s[i - 1] != 'u' || s[i - 2] != 'c' || s[i - 3] != '.')
		exit_and_free(d, FORMAT_ERROR);
}

void	flood(t_data *d, int x, int y)
{
	if (x < 0 || y < 0 || x >= d->c.cols + 2 || y >= d->c.rows + 2
		|| d->c.to_flood[y][x] == '1' || d->c.to_flood[y][x] == 'F')
		return ;
	if ((d->c.to_flood[y][x] != '1' && d->c.to_flood[y][x] != ' ')
		|| (d->c.to_flood[y][x] == 'W' || d->c.to_flood[y][x] == 'E'
		|| d->c.to_flood[y][x] == 'N' || d->c.to_flood[y][x] == 'S'))
	{
		verif(d);
		exit_and_free(d, FLOOD_ERROR);
	}
	d->c.to_flood[y][x] = 'F';
	flood(d, x + 1, y);
	flood(d, x - 1, y);
	flood(d, x, y + 1);
	flood(d, x, y - 1);
}

void	create_flood_map(t_data *d)
{
	int	i;
	int	j;

	d->c.to_flood = malloc(sizeof(char *) * (d->c.rows + 3));
	if (!d->c.to_flood)
		exit_and_free(d, ALLOC_ERROR);
	i = 0;
	while (i < d->c.rows + 2)
	{
		d->c.to_flood[i] = malloc(sizeof(char) * (d->c.cols + 3));
		if (!d->c.to_flood[i])
			exit_and_free(d, ALLOC_ERROR);
		j = 0;
		while (j < d->c.cols + 2)
		{
			d->c.to_flood[i][j] = ' ';
			j++;
		}
		d->c.to_flood[i][j] = '\0';
		i++;
	}
	d->c.to_flood[i] = NULL;
}

void	fill_flood_map(t_data *d)
{
	int	i;
	int	j;

	i = 0;
	while (d->c.map[i])
	{
		j = 0;
		while (d->c.map[i][j])
		{
			d->c.to_flood[i + 1][j + 1] = d->c.map[i][j];
			j++;
		}
		i++;
	}
}
