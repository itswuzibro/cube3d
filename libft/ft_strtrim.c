/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:42:24 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 18:47:04 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char const c, char const *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	count_set(char const *str, char const *set)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = ft_strlen(str) - 1;
	count = 0;
	while (str[i] && is_set(str[i], set) == 1)
	{
		count++;
		i++;
	}
	if (str[i] == '\0')
		return (count);
	while (j > 0 && is_set(str[j], set) == 1)
	{
		count++;
		j--;
	}
	return (count);
}

char	*ft_strtrim(char *s1, char const *set, int opt)
{
	int		i;
	int		j;
	int		k;
	int		setsize;
	char	*newstring;

	i = 0;
	j = ft_strlen(s1) - 1;
	k = 0;
	setsize = count_set(s1, set);
	newstring = malloc(sizeof(char) * (j - setsize + 2));
	if (!newstring)
		return (NULL);
	while (s1[i] && is_set(s1[i], set) == 1)
		i++;
	while (j > 0 && is_set(s1[j], set) == 1)
		j--;
	while (i <= j)
		newstring[k++] = s1[i++];
	newstring[k] = '\0';
	if (opt == 1)
		free(s1);
	return (newstring);
}
