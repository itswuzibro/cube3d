/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_gameplay_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:24:29 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 17:25:09 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

bool	is_out_of_map(int map_cols, int map_rows, int x, int y)
{
	if (x < 0 || x >= map_cols || y < 0 || y >= map_rows)
		return (true);
	return (false);
}

bool	is_wall(char **map, int x, int y)
{
	if (map[y][x] == CASE_WALL || map[y][x] == CASE_WINE
		|| map[y][x] == CASE_CDOOR)
		return (true);
	return (false);
}

bool	is_blocking_ray(char **map, int x, int y)
{
	if (map[y][x] == CASE_WALL || map[y][x] == CASE_WINE
		|| map[y][x] == CASE_CDOOR || map[y][x] == CASE_ODOOR)
		return (true);
	return (false);
}

bool	is_floor(char **map, int x, int y)
{
	if (map[y][x] == CASE_FLOOR || map[y][x] == CASE_ROOF
		|| map[y][x] == CASE_RIVER)
		return (true);
	return (false);
}

bool	is_walkable(t_data *d, float x, float y, float size)
{
	if (is_out_of_map(d->c.cols, d->c.rows, x + size, y)
		|| is_out_of_map(d->c.cols, d->c.rows, x - size, y)
		|| is_out_of_map(d->c.cols, d->c.rows, x, y + size)
		|| is_out_of_map(d->c.cols, d->c.rows, x, y - size))
		return (false);
	if (is_wall(d->c.map, x + size, y) || is_wall(d->c.map, x - size, y)
		|| is_wall(d->c.map, x, y + size) || is_wall(d->c.map, x, y - size))
		return (false);
	return (true);
}
