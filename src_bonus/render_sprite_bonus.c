/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:55:19 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 17:55:50 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static void	drawing_limit(t_scast *s)
{
	s->draw_start_y = -s->sprite_h / 2 + MIHEIGHT + s->vmove_screen;
	s->draw_end_y = s->sprite_h / 2 + MIHEIGHT + s->vmove_screen;
	if (s->draw_start_y < 0)
		s->draw_start_y = 0;
	if (s->draw_end_y >= HEIGHT)
		s->draw_end_y = HEIGHT - 1;
	s->draw_start_x = -s->sprite_w / 2 + s->screen_x;
	s->draw_end_x = s->sprite_w / 2 + s->screen_x;
	if (s->draw_start_x < 0)
		s->draw_start_x = 0;
	if (s->draw_end_x >= WIDTH)
		s->draw_end_x = WIDTH - 1;
	s->stripe_offset = -s->sprite_w / 2 + s->screen_x;
	s->stripe = s->draw_start_x - 1;
}

static bool	is_pixel_in_range(t_scast *s, t_img *img)
{
	if (s->stripe < 0 || s->stripe >= WIDTH)
		return (true);
	s->tex_x = (256 * (s->stripe - s->stripe_offset)
			* img->width / s->sprite_w) / 256;
	if (s->tex_x < 0 || s->tex_x >= img->width)
		return (true);
	return (false);
}

static void	draw_and_update_depth(t_data *d, t_scast *s, unsigned int c, int y)
{
	mlx_set_pixel(&d->i, s->stripe, y, c);
	d->z_buffer[y * WIDTH + s->stripe] = s->transform_y;
}

static void	calculate_sprite_tx_line(t_scast *s, t_img *img, int y)
{
	s->d_y = (y - s->vmove_screen) * 256
		- HEIGHT * 128 + s->sprite_h * 128;
	s->tex_y = ((s->d_y * img->height) / s->sprite_h) / 256;
}

void	spritecasting(t_data *d, t_img *img, t_fvector pos, t_transform t)
{
	t_scast			s;
	int				y;
	unsigned int	color;

	s = (t_scast){0};
	if (init_scasting(d, &s, &pos, &t) == true)
		return ;
	drawing_limit(&s);
	while (++s.stripe < s.draw_end_x)
	{
		if (is_pixel_in_range(&s, img) == true)
			break ;
		y = s.draw_start_y - 1;
		while (++y < s.draw_end_y)
		{
			calculate_sprite_tx_line(&s, img, y);
			if (s.tex_y < 0 || s.tex_y >= img->height || y < 0 || y >= HEIGHT)
				continue ;
			color = img->addr[img->width * s.tex_y + s.tex_x];
			if ((color & 0x00FFFFFF) != 0
				&& s.transform_y < d->z_buffer[y * WIDTH + s.stripe])
				draw_and_update_depth(d, &s, color, y);
		}
	}
}
