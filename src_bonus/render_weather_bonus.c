/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_weather_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:24:32 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 17:58:12 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static void	retrigger_rain(t_rain *r)
{
	if (r->pos_x >= WIDTH)
		r->pos_x = 0;
	if (r->pos_y >= HEIGHT)
		r->pos_y = 0;
	if (r->pos_x < 0)
		r->pos_x = WIDTH - 1;
	if (r->pos_y < 0)
		r->pos_y = HEIGHT - 1;
}

void	launch_rain(t_data *d)
{
	int	i;

	i = 0;
	while (i < RAIN_C)
	{
		rain(d, &d->rain[i], d->delta_time);
		i++;
	}
}

void	rain(t_data *d, t_rain *r, float delta_time)
{
	float	x;
	float	y;

	y = 0;
	x = 0;
	r->pos_x = r->pos_x + r->dir_x * r->speed * delta_time;
	r->pos_y = r->pos_y + r->dir_y * r->speed * delta_time;
	retrigger_rain(r);
	while (y < r->len)
	{
		if (d->game_state == MENU && d->light == false)
			mlx_set_pixel(&d->i, r->pos_x + x, r->pos_y + y, BLOOD);
		else if (d->game_state == MENU && d->light == true)
			mlx_set_pixel(&d->i, r->pos_x + x, r->pos_y + y, 0x552222);
		else
			mlx_set_pixel(&d->i, r->pos_x + x, r->pos_y + y, 0x808080);
		x += r->dir_x;
		y += r->dir_y;
	}
}

static void	screen_darken(t_data *d, int nb)
{
	int				x;
	int				y;
	int				dark_loop;
	unsigned int	color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			color = mlx_get_pixel(&d->i, x, y);
			dark_loop = 0;
			while (dark_loop < nb)
			{
				color = (color >> 1) & 8355711;
				dark_loop++;
			}
			mlx_set_pixel(&d->i, x, y, color);
			x++;
		}
		y++;
	}
}

void	lightning(t_data *d)
{
	if (d->game_state == MENU)
		copypaste_img(&d->intro, &d->i, 0, 0);
	if (d->light == true)
	{
		if (d->game_state == MENU && d->l_duration < 300)
			screen_darken(d, 1);
		if (gettime() - d->last_lightning > d->l_duration)
		{
			d->light = false;
			d->l_duration = (rand() % 850) + 50;
			d->n_lightning = (rand() % 3500);
		}
	}
	else
	{
		if (d->game_state == MENU)
			screen_darken(d, 2);
		if (gettime() - d->last_lightning > d->n_lightning)
		{
			d->last_lightning = gettime();
			d->light = true;
		}
	}
}
