/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:27:16 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/15 02:39:47 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	init_structures(t_data *d)
{
	d->last_frame = gettime();
	d->game_launch = true;
	d->z_buffer = malloc(sizeof(float) * WIDTH * HEIGHT);
	if (!d->z_buffer)
		exit_and_free(d, ALLOC_ERROR);
	d->minimap_size = 5;
	d->minimap_press = 0;
	d->minimap_pix = 3;
}
