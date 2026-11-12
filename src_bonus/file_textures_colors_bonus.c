/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_textures_colors_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:36:28 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 20:14:15 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

unsigned int	extract_rbg_value(t_data *d, char *value)
{
	char			**tmp;
	int				i;
	unsigned int	rgb_slot;

	i = -1;
	tmp = ft_split(value, ',');
	if (ft_tablen(tmp) != 3)
	{
		ft_free_tab(tmp);
		exit_and_free(d, SD_ERR);
	}
	while (++i < 3)
	{
		tmp[i] = ft_char_kill(tmp[i], ' ', 1);
		if (!tmp[i])
			exit_and_free(d, ALLOC_ERROR);
		if (ft_atoi(tmp[i]) < 0 || ft_atoi(tmp[i]) > 255)
			(ft_free_tab(tmp), exit_and_free(d, RGB_ERR));
		if (ft_str_isdigit(tmp[i]) == 0)
			(ft_free_tab(tmp), exit_and_free(d, RGB_VAL));
	}
	rgb_slot = create_trgb(0, ft_atoi(tmp[0]),
			ft_atoi(tmp[1]), ft_atoi(tmp[2]));
	ft_free_tab(tmp);
	return (rgb_slot);
}

static void	get_basic_config(t_data *d, char *str)
{
	if (str[0] == 'N' && str[1] == 'O')
	{
		free(d->c.no);
		d->c.no = ft_strtrim_secure(d, str + 2, " \t", 0);
	}
	else if (str[0] == 'S' && str[1] == 'O')
	{
		free(d->c.so);
		d->c.so = ft_strtrim_secure(d, str + 2, " \t", 0);
	}
	else if (str[0] == 'E' && str[1] == 'A')
	{
		free(d->c.ea);
		d->c.ea = ft_strtrim_secure(d, str + 2, " \t", 0);
	}
	else if (str[0] == 'W' && str[1] == 'E')
	{
		free(d->c.we);
		d->c.we = ft_strtrim_secure(d, str + 2, " \t", 0);
	}
}

static void	get_color_config(t_data *d, char *str)
{
	if (str[0] == 'C')
	{
		free(d->c.c);
		d->c.c = ft_strtrim_secure(d, str + 1, " \t", 0);
	}
	else if (str[0] == 'F')
	{
		free(d->c.f);
		d->c.f = ft_strtrim_secure(d, str + 1, " \t", 0);
	}
}

static void	get_extra_config(t_data *d, char *str)
{
	if (!ft_strncmp(str, "RAIN", 4))
		d->weather = true;
	else if (!ft_strncmp(str, "RIVER", 5))
	{
		free(d->c.river_path);
		d->c.river_path = ft_strtrim_secure(d, str + 5, " \t", 0);
	}
	else if (!ft_strncmp(str, "ROOF", 4))
	{
		free(d->c.roof_path);
		d->c.roof_path = ft_strtrim_secure(d, str + 4, " \t", 0);
	}
}

void	get_textures_and_colors(t_data *d)
{
	int	i;

	i = 0;
	while (d->c.sd[i] && !(d->c.no && d->c.so
			&& d->c.we && d->c.ea && d->c.c && d->c.f))
	{
		get_basic_config(d, d->c.sd[i]);
		get_color_config(d, d->c.sd[i]);
		get_extra_config(d, d->c.sd[i]);
		i++;
	}
	if (!d->c.sd[i] && d->c.no && d->c.so
		&& d->c.we && d->c.ea && d->c.c && d->c.f)
		exit_and_free(d, "Error: No map\n");
	if (!d->c.sd[i])
		exit_and_free(d, TXTR_ERR);
	while (!ft_strcmp(d->c.sd[i], ""))
		i++;
	d->c.rows = ft_tablen(d->c.sd) - i;
}
