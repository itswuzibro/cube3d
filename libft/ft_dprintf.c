/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:10:13 by jde-sain          #+#    #+#             */
/*   Updated: 2024/10/23 22:51:38 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_dputchar_fd(char c, int fd, int *count)
{
	write (fd, &c, 1);
	*count += 1;
}

static void	ft_dputstr_fd(char *s, int fd, int *count)
{
	int	len;

	len = ft_strlen(s);
	if (!s)
		return ;
	write (fd, s, len);
	*count += len;
}

static void	ft_dputnbr_base(long long int nbr, char *base, int fd, int *count)
{
	if (nbr < 0)
	{
		ft_dputchar_fd('-', fd, count);
		nbr = -nbr;
	}
	if (nbr / ft_strlen(base))
		ft_dputnbr_base(nbr / ft_strlen(base), base, fd, count);
	ft_dputchar_fd(base[nbr % ft_strlen(base)], fd, count);
}

static void	conversion(va_list args, char c, int fd, int *count)
{
	if (c == 'c')
		ft_dputchar_fd(va_arg(args, int), fd, count);
	if (c == 's')
		ft_dputstr_fd(va_arg(args, char *), fd, count);
	if (c == 'd')
		ft_dputnbr_base(va_arg(args, int), "0123456789", fd, count);
}

int	ft_dprintf(int fd, const char *str, ...)
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
			ft_dputchar_fd(str[i], fd, &count);
		if (str[i] == 37)
		{
			conversion(args, str[i + 1], fd, &count);
			i++;
		}
		i++;
	}
	va_end(args);
	return (count);
}
