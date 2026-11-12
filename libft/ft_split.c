/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:48:19 by jde-sain          #+#    #+#             */
/*   Updated: 2024/10/22 21:04:39 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *str, char c)
{
	int	i;
	int	token;
	int	count;

	i = 0;
	token = 0;
	count = 0;
	while (str[i])
	{
		token = 0;
		while (str[i] && str[i] == c)
			i++;
		while (str[i] && str[i] != c)
		{
			token = 1;
			i++;
		}
		while (str[i] && str[i] == c)
			i++;
		if (token == 1)
			count++;
	}
	return (count);
}

static char	*get_part(char const *str, char c)
{
	int		i;
	int		j;
	char	*part;

	i = 0;
	j = 0;
	while (str[i] && str[i] != c)
		i++;
	part = malloc(sizeof(char) * (i + 1));
	if (!part)
		return (NULL);
	while (j < i)
	{
		part[j] = str[j];
		j++;
	}
	part[j] = '\0';
	return (part);
}

static void	*free_cascade(char **tab, int i)
{
	i--;
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**tab;
	int		count;

	if (!s)
		return (NULL);
	i = 0;
	count = count_words(s, c);
	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	while (i < count)
	{
		while (*s && *s == c)
			s++;
		tab[i] = get_part(s, c);
		if (!tab[i])
			return (free_cascade(tab, i));
		while (*s && *s != c)
			s++;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
