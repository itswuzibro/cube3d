/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:22:17 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/04 20:03:40 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	unsigned char	tmpc;

	i = 0;
	tmpc = c;
	while (s[i])
	{
		if (s[i] == tmpc)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == tmpc)
		return ((char *)s + i);
	return (NULL);
}
