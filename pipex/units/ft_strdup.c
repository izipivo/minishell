/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdursley <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 23:01:36 by pdursley          #+#    #+#             */
/*   Updated: 2021/10/15 23:01:37 by pdursley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*ft_strdup(const char *str)
{
	char	*string;
	int		len;
	int		i;

	len = ft_strlen(str);
	string = malloc(sizeof(char) * len + 1);
	if (string == NULL)
		return (NULL);
	i = 0;
	while (len != 0)
	{
		string[i++] = *(str++);
		len--;
	}
	string[i] = '\0';
	return (string);
}
