/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:14:51 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/04 20:03:56 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

void	cleaning(char *save)
{
	free(save);
	save = NULL;
}

char	*read_loop(int fd, char	*save)
{
	char	*buffer;
	int		stop;
	int		i;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	stop = 1;
	i = 0;
	while (stop != 0)
	{
		stop = read(fd, buffer, BUFFER_SIZE);
		if (stop == -1)
			return (free (buffer), cleaning(save), NULL);
		buffer[stop] = '\0';
		save = ft_strjoin_gnl(save, buffer);
		while (save[i])
		{
			if (save[i] == '\n')
				return (free(buffer), save);
			i++;
		}
	}
	return (free(buffer), save);
}

char	*get_line(char *save)
{
	char	*get_line;
	int		i;

	i = 0;
	if (save[0] == 0)
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	get_line = malloc (sizeof(char) * (i + 2));
	if (!get_line)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		get_line[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		get_line[i] = save[i];
		i++;
	}
	get_line[i] = '\0';
	return (get_line);
}

char	*get_saved(char *save)
{
	char	*get_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\0')
	{
		free(save);
		return (NULL);
	}
	get_line = malloc (sizeof(char) * (ft_strlen_gnl(save) - i + 1));
	if (!get_line)
		return (NULL);
	i++;
	while (save[i] != '\0')
		get_line[j++] = save[i++];
	get_line[j] = '\0';
	free (save);
	return (get_line);
}

char	*get_next_line(int fd)
{
	static char	*save = NULL;
	char		*line;

	if (fd == 77)
	{
		free(save);
		save = NULL;
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = read_loop(fd, save);
	if (!save)
		return (NULL);
	line = get_line(save);
	save = get_saved(save);
	return (line);
}
