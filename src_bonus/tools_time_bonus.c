/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_time_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:22:35 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 17:26:21 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

time_t	gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	animation(int nb_img, int fps)
{
	static int		count = -1;
	static time_t	time = 0;

	if (gettime() - time > fps)
	{
		count++;
		time = gettime();
	}
	count %= nb_img;
	return (count);
}
