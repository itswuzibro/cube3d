/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_portal_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:23:27 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 15:23:28 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	update_portal(t_data *d)
{
	if (distance (d->p.pos, d->portal.pos) < 5.0f)
	{
		reset_flip(&d->portal.descending);
		reset_flip(&d->portal.far);
		if (!d->portal.ascending.completed)
			d->portal.current_anim = &d->portal.ascending;
		else
			d->portal.current_anim = &d->portal.close;
	}
	else
	{
		reset_flip(&d->portal.ascending);
		reset_flip(&d->portal.close);
		if (!d->portal.descending.completed)
			d->portal.current_anim = &d->portal.descending;
		else
			d->portal.current_anim = &d->portal.far;
	}
	update_flipbook(d->portal.current_anim);
}
