/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:37:50 by sdonny            #+#    #+#             */
/*   Updated: 2022/05/01 16:28:37 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const	*s2)
{
	char	*joined;
	int		i;

	i = -1;
	if (!s1 && !s2)
	{
		return (0);
	}
	else if (!s1)
		joined = (char *) malloc(ft_strlen(s2) + 1);
	else if (!s2)
		joined = (char *) malloc(ft_strlen(s1) + 1);
	else
		joined = (char *) malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!joined)
	{
		ft_putstr_fd("ft_strjoin: malloc rip\n", 2);
		return (0);
	}
	while (s1 && *s1)
		joined[++i] = *s1++;
	while (s2 && *s2)
		joined[++i] = *s2++;
	joined[++i] = '\0';
	return (joined);
}
