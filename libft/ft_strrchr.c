/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:32:31 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/04 20:04:01 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	tmpc;

	i = 0;
	tmpc = c;
	while (s[i])
		i++;
	while (i >= 0 && s[i] != tmpc)
		i--;
	if (i == -1)
		return (NULL);
	return ((char *)s + i);
}
