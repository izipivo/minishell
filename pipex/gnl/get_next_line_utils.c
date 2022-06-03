/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdursley <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:41:08 by pdursley          #+#    #+#             */
/*   Updated: 2021/11/14 14:41:10 by pdursley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *str, int ch)
{
	char			*string;
	unsigned char	c;

	c = (char)ch;
	string = (char *)str;
	while (*string != c)
	{
		if (*string == '\0')
		{
			return ((char *) NULL);
		}
		string++;
	}
	return (string);
}
