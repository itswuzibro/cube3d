/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_kill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:44:46 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 20:15:14 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_char_kill(char *str, char set, int opt)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	s = ft_strdup(str);
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] != set)
		{
			s[j] = s[i];
			j++;
			i++;
		}
		else
			i++;
	}
	s[j] = '\0';
	if (opt == 1)
		free (str);
	return (s);
}
