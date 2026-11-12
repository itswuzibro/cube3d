/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:15:17 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/04 20:05:11 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*char	ft_nextchar(unsigned int i, char c)
{
	c = c + i;
	return (c);
}*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	slen;
	char	*nstr;

	i = 0;
	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	nstr = malloc(sizeof(char) * slen + 1);
	if (!nstr)
		return (NULL);
	while (i < slen)
	{
		nstr[i] = f(i, s[i]);
		i++;
	}
	nstr[i] = '\0';
	return (nstr);
}
