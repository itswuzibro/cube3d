/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:10:13 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/04 20:04:54 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	get_adress(void	*content, int *count)
{
	if (!content)
	{
		write (1, "(nil)", 5);
		*count += 5;
	}
	else
	{
		write (1, "0x", 2);
		*count += 2;
		ft_upnb((unsigned long long int)content, "0123456789abcdef", count);
	}
}

static void	conversion(va_list args, char c, int *count)
{
	if (c == 'c')
		ft_putchar(va_arg(args, int), count);
	if (c == 's')
		ft_putstr(va_arg(args, char *), count);
	if (c == 'p')
		get_adress(va_arg(args, void *), count);
	if (c == 'd')
		ft_putnbr_base(va_arg(args, int), "0123456789", count);
	if (c == 'i')
		ft_putnbr_base(va_arg(args, int), "0123456789", count);
	if (c == 'u')
		ft_putnbr_base(va_arg(args, unsigned int), "0123456789", count);
	if (c == 'x')
		ft_putnbr_base(va_arg(args, unsigned int), "0123456789abcdef", count);
	if (c == 'X')
		ft_putnbr_base(va_arg(args, unsigned int), "0123456789ABCDEF", count);
	if (c == '%')
		ft_putchar('%', count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		count;

	va_start(args, str);
	i = 0;
	count = 0;
	if (str == 0)
		return (-1);
	while (str[i])
	{
		if (str[i] != 37)
			ft_putchar(str[i], &count);
		if (str[i] == 37)
		{
			conversion(args, str[i + 1], &count);
			i++;
		}
		i++;
	}
	va_end(args);
	return (count);
}
