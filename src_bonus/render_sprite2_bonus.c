/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:54:34 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 16:55:10 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

int	rotate_sprite(t_data *d, t_fvector pos, float angle, int num_img)
{
	float	angle_to_player;
	float	relative_angle;
	float	angle_per_sprite;
	int		sprite_index;

	angle_to_player = atan2f(d->p.pos.y - pos.y, d->p.pos.x - pos.x);
	relative_angle = angle_to_player - angle;
	while (relative_angle < 0)
		relative_angle += 2 * PI;
	while (relative_angle >= 2 * PI)
		relative_angle -= 2 * PI;
	angle_per_sprite = 2 * PI / num_img;
	sprite_index = (int)((relative_angle + (angle_per_sprite / 2))
			/ angle_per_sprite) % num_img;
	return (sprite_index);
}

void	update_sprite_anim(t_data *d, t_flip *flip, t_fvector pos, float angle)
{
	int	rot_index;
	int	combine_index;

	rot_index = 0;
	update_flipbook(flip);
	if (flip->nb_direction > 1)
		rot_index = rotate_sprite(d, pos, angle, flip->nb_direction);
	combine_index = flip->frame_per_dir * rot_index + flip->index;
	flip->frame = &flip->imgs[combine_index];
}
