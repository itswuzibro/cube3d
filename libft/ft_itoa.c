/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:10:23 by jean-loup         #+#    #+#             */
/*   Updated: 2025/09/04 20:03:31 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countdigit(long int nb)
{
	long int	count;

	count = 0;
	if (nb < 0)
		count++;
	if (nb == 0)
		count++;
	while (nb != 0)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long int	count;
	long int	nb;
	char		*str;

	nb = n;
	count = countdigit(nb);
	str = malloc(sizeof(char) * count + 1);
	if (!str)
		return (NULL);
	if (nb < 0)
	{
		nb = -nb;
		str[0] = '-';
	}
	str[count] = '\0';
	count--;
	if (nb == 0)
		str[count] = '0';
	while (nb != 0)
	{
		str[count] = nb % 10 + 48;
		nb = nb / 10;
		count--;
	}
	return (str);
}
