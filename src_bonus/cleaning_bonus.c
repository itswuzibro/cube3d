/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:29:22 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 20:05:20 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

char	*ft_strtrim_secure(t_data *d, char *s1, char const *set, int opt)
{
	char	*s;

	s = ft_strtrim(s1, set, opt);
	if (!s)
		exit_and_free(d, ALLOC_ERROR);
	return (s);
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

static void	more_img_cleaning(t_data *d)
{
	imgs_destroyer(d, d->wizard_walk, 32);
	imgs_destroyer(d, d->wizard_atk, 3);
	imgs_destroyer(d, d->wizard_death, 19);
	imgs_destroyer(d, d->wizard_idle, 16);
	imgs_destroyer(d, d->wizard_pain, 8);
	imgs_destroyer(d, d->weredragon_walk, 48);
	imgs_destroyer(d, d->weredragon_attack, 2);
	imgs_destroyer(d, d->weredragon_death, 9);
	imgs_destroyer(d, d->weredragon_idle, 16);
	imgs_destroyer(d, d->weredragon_pain, 8);
	imgs_destroyer(d, d->portal_far, 8);
	imgs_destroyer(d, d->portal_close, 8);
	imgs_destroyer(d, d->portal_ascending, 3);
	imgs_destroyer(d, d->portal_descending, 3);
	imgs_destroyer(d, d->numbers, 10);
	imgs_destroyer(d, &d->crosshair, 1);
	imgs_destroyer(d, &d->ending, 1);
	imgs_destroyer(d, &d->right, 1);
	imgs_destroyer(d, &d->big_right, 1);
	imgs_destroyer(d, d->player_nuke, 6);
	imgs_destroyer(d, &d->i, 1);
}

static void	img_cleaning(t_data *d)
{
	imgs_destroyer(d, &d->intro, 1);
	imgs_destroyer(d, &d->title, 1);
	imgs_destroyer(d, &d->launch, 1);
	imgs_destroyer(d, &d->paused, 1);
	imgs_destroyer(d, &d->go_on, 1);
	imgs_destroyer(d, &d->quit, 1);
	imgs_destroyer(d, d->skull, 18);
	imgs_destroyer(d, d->wall, 4);
	imgs_destroyer(d, &d->floor, 1);
	imgs_destroyer(d, &d->roof, 1);
	imgs_destroyer(d, d->door, 2);
	imgs_destroyer(d, &d->wine, 1);
	imgs_destroyer(d, &d->river, 1);
	imgs_destroyer(d, &d->player, 1);
	imgs_destroyer(d, d->border, 2);
	imgs_destroyer(d, d->status, 2);
	imgs_destroyer(d, d->health, 2);
	imgs_destroyer(d, &d->health_empty, 1);
	imgs_destroyer(d, d->interact, 4);
	imgs_destroyer(d, d->attack, 9);
	imgs_destroyer(d, d->projectile_player, 4);
	imgs_destroyer(d, d->projectile_wizard, 4);
	imgs_destroyer(d, d->blood_splat, 6);
}

void	exit_and_free(t_data *d, char *errormsg)
{
	img_cleaning(d);
	more_img_cleaning(d);
	ft_free_tab(d->c.sd);
	ft_free_tab(d->c.map);
	ft_free_tab(d->c.to_flood);
	free(d->z_buffer);
	free(d->c.c);
	free(d->c.f);
	free(d->c.no);
	free(d->c.so);
	free(d->c.ea);
	free(d->c.we);
	free(d->c.river_path);
	free(d->c.roof_path);
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
