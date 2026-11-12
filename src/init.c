/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:27:16 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/09 17:44:24 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_data(t_data *d)
{
	d->last_frame = gettime();
	d->mlx = NULL;
	d->win = NULL;
	d->line_count = 0;
	d->line_lenght = 0;
	d->p.plane.x = 0;
	d->p.plane.y = 0;
	d->p.angle = 0;
	d->p.movespeed = 2;
	d->p.rotspeed = PI / 2;
}

void	init_config(t_config *config)
{
	config->ea = NULL;
	config->so = NULL;
	config->we = NULL;
	config->no = NULL;
	config->c = NULL;
	config->f = NULL;
	config->sd = NULL;
	config->map = NULL;
	config->to_flood = NULL;
	config->cols = 0;
	config->rows = 0;
}

void	init_img(t_img *img)
{
	img->ptr = NULL;
	img->addr = NULL;
	img->bits_per_pixel = 0;
	img->line_length = 0;
	img->endian = 0;
}

void	init_keys(t_keyboard *k)
{
	k->w = false;
	k->z = false;
	k->a = false;
	k->q = false;
	k->s = false;
	k->d = false;
	k->m = false;
	k->enter = false;
	k->maj = false;
	k->up_arrow = false;
	k->down_arrow = false;
	k->left_arrow = false;
	k->right_arrow = false;
}
