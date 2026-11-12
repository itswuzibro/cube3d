/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:25:32 by jde-sain          #+#    #+#             */
/*   Updated: 2024/01/15 18:19:31 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

int	ft_strlen_gnl(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strcat_gnl(char *dst, char *src)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (dst[i])
		i++;
	while (src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strdup_gnl(const char *s)
{
	int		i;
	int		size;
	char	*tab;

	i = 0;
	size = ft_strlen_gnl(s);
	tab = malloc(sizeof(char) * (size + 1));
	if (!tab)
		return (NULL);
	while (s[i])
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		totalsize;
	char	*newstring;
	int		i;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	totalsize = (ft_strlen_gnl(s1) + ft_strlen_gnl(s2));
	newstring = malloc(sizeof(char) * totalsize + 1);
	if (!newstring)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		newstring[i] = s1[i];
		i++;
	}
	newstring[i] = '\0';
	ft_strcat_gnl(newstring, (s2));
	free(s1);
	return (newstring);
}
