/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_blood_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:50:48 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 17:48:14 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	init_blood(t_data *d)
{
	int	i;

	i = 0;
	while (i < MAX_BLOOD)
	{
		d->p.blood[i].active = false;
		d->p.blood[i].img = &d->blood_splat[rand() % 6];
		d->p.blood[i].pos.x = rand() % WIDTH
			- d->p.blood[i].img->width / 2;
		d->p.blood[i].pos.y = rand() % HEIGHT
			- d->p.blood[i].img->height / 2;
		i++;
	}
}
