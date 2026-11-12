/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:45:41 by jde-sain          #+#    #+#             */
/*   Updated: 2023/12/11 16:48:58 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char			*str;
	unsigned int		i;
	char				tmpc;

	str = (char *)s;
	i = 0;
	tmpc = c;
	while (i < n)
	{
		if (str[i] == tmpc)
			return ((char *)str + i);
		i++;
	}
	return (0);
}
