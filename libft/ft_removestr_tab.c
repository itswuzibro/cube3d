/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_removestr_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:44:36 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/03 19:44:40 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_removestr_tab(char *str, char **tab)
{
	int		i;
	int		j;
	char	**ntab;

	i = ft_tablen(tab);
	j = 0;
	ntab = malloc(sizeof(char *) * (i));
	if (!ntab)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		if (ft_strcmp(str, tab[i]) == 0)
			i++;
		else
			ntab[j++] = ft_strdup(tab[i++]);
	}
	ntab[j] = NULL;
	ft_free_tab(tab);
	return (ntab);
}
