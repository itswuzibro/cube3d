/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:26:28 by jde-sain          #+#    #+#             */
/*   Updated: 2023/12/14 18:24:08 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c, int *count)
{
	write (1, &c, 1);
	*count += 1;
}

void	ft_putstr(char *str, int *count)
{
	int	i;

	i = 0;
	if (!str)
	{
		*count += write (1, "(null)", 6);
		return ;
	}
	while (str[i])
	{
		*count += 1;
		i++;
	}
	write (1, str, i);
}

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putnbr_base(long long int nbr, char *base, int *count)
{
	if (nbr < 0)
	{
		ft_putchar('-', count);
		nbr = -nbr;
	}
	if (nbr / ft_strlen(base))
		ft_putnbr_base(nbr / ft_strlen(base), base, count);
	ft_putchar(base[nbr % ft_strlen(base)], count);
}

void	ft_upnb(unsigned long long int nbr, char *base, int *count)
{
	if (nbr / ft_strlen(base))
		ft_upnb(nbr / ft_strlen(base), base, count);
	ft_putchar(base[nbr % ft_strlen(base)], count);
}
