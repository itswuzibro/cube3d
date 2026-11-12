/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:29:22 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 20:06:48 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

char	*ft_strtrim_secure(t_data *d, char *s1, char const *set, int opt)
{
	char	*s;

	s = ft_strtrim(s1, set, opt);
	if (!s)
		exit_and_free(d, ALLOC_ERROR);
	return (s);
}

int	mouse_quit(t_data *d)
{
	exit_and_free(d, "Closing game..\n");
	return (0);
}

void	exit_and_free(t_data *d, char *errormsg)
{
	imgs_destroyer(d, d->wall, 4);
	ft_free_tab(d->c.sd);
	ft_free_tab(d->c.map);
	ft_free_tab(d->c.to_flood);
	free(d->c.no);
	free(d->c.so);
	free(d->c.ea);
	free(d->c.we);
	free(d->c.c);
	free(d->c.f);
	if (d->win)
		mlx_destroy_window(d->mlx, d->win);
	if (d->mlx)
	{
		mlx_destroy_display(d->mlx);
		free(d->mlx);
	}
	write (2, errormsg, ft_strlen(errormsg));
	exit(1);
}
