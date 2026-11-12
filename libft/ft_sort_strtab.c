/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_strtab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:44:28 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 18:51:09 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_sort_strtab(char **tab)
{
	int	i;
	int	size;

	i = 0;
	while (tab[i])
		i++;
	size = i;
	i = 0;
	while (i < size - 1)
	{
		if (ft_strcmp(tab[i], tab[i + 1]) > 0)
		{
			ft_swap_str(&tab[i], &tab[i + 1]);
			i = 0;
		}
		else
			i++;
	}
	return (tab);
}
