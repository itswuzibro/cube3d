/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:14:50 by jde-sain          #+#    #+#             */
/*   Updated: 2024/10/30 20:39:08 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2, int option)
{
	int		totalsize;
	char	*newstring;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	totalsize = (ft_strlen(s1) + ft_strlen((s2)));
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
	ft_strcat(newstring, s2);
	if (option == 1)
		free(s1);
	else if (option == 2)
		free(s2);
	else if (option == 3)
		(free(s1), free(s2));
	return (newstring);
}
