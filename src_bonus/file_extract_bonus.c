/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_extract_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:36:25 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 20:12:17 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static int	count_line_sd(t_data *d, char *path)
{
	int		fd;
	int		count;
	char	*str;

	count = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		exit_and_free(d, FD_ERROR);
	str = get_next_line(fd);
	while (str)
	{
		count++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (count);
}

static void	stock_sd(t_data *d, char *path)
{
	int		i;
	int		fd;
	char	*str;

	i = 0;
	d->c.sd = malloc(sizeof(char *) * (count_line_sd(d, path) + 1));
	if (!d->c.sd)
		exit_and_free(d, ALLOC_ERROR);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		exit_and_free(d, FD_ERROR);
	str = get_next_line(fd);
	while (str)
	{
		d->c.sd[i] = ft_strtrim_secure(d, str, "\n", 1);
		if (!d->c.sd[i])
			(close(fd), exit_and_free(d, ALLOC_ERROR));
		i++;
		str = get_next_line(fd);
	}
	d->c.sd[i] = NULL;
	close(fd);
}

static void	get_map(t_data *d)
{
	int	i;
	int	map_start;
	int	len;

	i = 0;
	map_start = ft_tablen(d->c.sd) - d->c.rows;
	d->c.map = malloc(sizeof(char *) * (d->c.rows + 1));
	if (!d->c.map)
		exit_and_free(d, ALLOC_ERROR);
	i = 0;
	while (d->c.sd[map_start + i])
	{
		d->c.map[i] = ft_strdup(d->c.sd[map_start + i]);
		if (!d->c.map[i])
			exit_and_free(d, ALLOC_ERROR);
		len = ft_strlen(d->c.map[i]);
		if (len > d->c.cols)
			d->c.cols = len;
		i++;
	}
	d->c.map[i] = NULL;
}

static void	validate_map_format(t_data *d, char *s)
{
	int	i;

	i = 0;
	if (ft_strlen(s) < 3)
		exit_and_free(d, FORMAT_ERROR);
	while (s[i])
		i++;
	i--;
	if (s[i] != 'b' || s[i - 1] != 'u' || s[i - 2] != 'c' || s[i - 3] != '.')
		exit_and_free(d, FORMAT_ERROR);
}

void	file_extract(t_data *d, char *path)
{
	validate_map_format(d, path);
	stock_sd(d, path);
	get_textures_and_colors(d);
	get_map(d);
	d->c.c_color = extract_rbg_value(d, d->c.c);
}
