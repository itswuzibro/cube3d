/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_to_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 18:49:38 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 18:49:50 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*tab_to_string(char **t)
{
	char	*s;
	int		i;

	i = 0;
	s = ft_strdup("");
	while (t[i])
	{
		s = ft_strjoin(s, t[i], 1);
		if (t[i + 1])
			s = ft_strjoin(s, " ", 1);
		i++;
	}
	return (s);
}
