/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_flipbooks_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:56:56 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 15:57:26 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	reset_flip(t_flip *flip)
{
	flip->last_update = gettime();
	flip->index = 0;
	flip->stopped = false;
	flip->completed = false;
	flip->event = false;
	flip->event_triggered = false;
}

void	set_flip_core(t_flip *flip, t_img *imgs, int frame_per_dir, int nb_dir)
{
	flip->imgs = imgs;
	flip->frame = &imgs[0];
	flip->frame_per_dir = frame_per_dir;
	flip->nb_direction = nb_dir;
	flip->is_durty = true;
}

void	set_flip_time(t_flip *flip, int loops, int interval, int event_frame)
{
	flip->loops = loops;
	flip->interval = interval;
	flip->event_frame = event_frame;
}
