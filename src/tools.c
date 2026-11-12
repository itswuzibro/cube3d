/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:24:29 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/17 17:47:15 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

unsigned int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

time_t	gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	imgs_nullifier(t_img *img, int nb_img)
{
	int	i;

	i = 0;
	while (i < nb_img)
	{
		img[i].ptr = NULL;
		i++;
	}
}

void	imgs_destroyer(t_data *d, t_img *img, int nb_img)
{
	int	i;

	i = 0;
	while (i < nb_img)
	{
		if (img[i].ptr)
			mlx_destroy_image(d->mlx, img[i].ptr);
		i++;
	}
}
