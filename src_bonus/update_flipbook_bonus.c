/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_flipbook_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 22:42:41 by injah             #+#    #+#             */
/*   Updated: 2025/09/16 13:51:03 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static void	flipbook_event(t_flip *flip)
{
	if (flip->index == flip->event_frame && !flip->event_triggered)
	{
		flip->event = true;
		flip->event_triggered = true;
	}
	else
		flip->event_triggered = false;
}

static void	flipbook_loop(t_flip *flip)
{
	flip->loops--;
	if (flip->loops == 0)
	{
		flip->index = flip->frame_per_dir - 1;
		flip->stopped = true;
	}
}

static void	flipbook_manage_options(t_flip *flip)
{
	if (flip->event_frame != -1)
		flipbook_event(flip);
	if (flip->index >= flip->frame_per_dir)
	{
		flip->completed = true;
		flip->index = 0;
		if (flip->loops != -1)
			flipbook_loop(flip);
	}
}

void	update_flipbook(t_flip *flip)
{
	time_t	now;

	if (flip->stopped)
		return ;
	if (flip->is_durty)
	{
		reset_flip(flip);
		flip->is_durty = false;
	}
	flip->frame = &flip->imgs[flip->index];
	now = gettime();
	flip->completed = false;
	flip->event = false;
	if (now - flip->last_update > flip->interval)
	{
		flip->last_update = now;
		flip->index++;
		flipbook_manage_options(flip);
	}
}
