/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdursley <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 21:44:24 by pdursley          #+#    #+#             */
/*   Updated: 2021/10/14 21:44:25 by pdursley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_strncmp(const char *str1, const char *str2, size_t vol)
{
	unsigned int	i;
	unsigned char	*string1;
	unsigned char	*string2;

	string1 = (unsigned char *)str1;
	string2 = (unsigned char *)str2;
	i = 0;
	if (*string1 == '\0' && *string2 == '\0')
		return (0);
	while (i < vol && string1[i] && string2[i])
	{
		if (string1[i] == string2[i])
			i++;
		else
			return (string1[i] - string2[i]);
	}
	if (i < vol && (!string1[i] || !string2[i]))
		return (string1[i] - string2[i]);
	return (0);
}
