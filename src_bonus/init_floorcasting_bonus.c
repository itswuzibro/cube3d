/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_floorcasting_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:06:32 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 16:14:48 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	init_floorcasting(t_data *d, t_floorcast *fc)
{
	fc->ray_dir_l.x = d->p.dir.x - d->p.plane.x;
	fc->ray_dir_l.y = d->p.dir.y - d->p.plane.y;
	fc->ray_dir_r.x = d->p.dir.x + d->p.plane.x;
	fc->ray_dir_r.y = d->p.dir.y + d->p.plane.y;
	fc->step.x = (fc->ray_dir_r.x - fc->ray_dir_l.x) / WIDTH;
	fc->step.y = (fc->ray_dir_r.y - fc->ray_dir_l.y) / WIDTH;
	fc->pos_z = 0.5f * HEIGHT;
	fc->cell_case = 0;
}
