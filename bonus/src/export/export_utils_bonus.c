/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdursley <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:21:12 by pdursley          #+#    #+#             */
/*   Updated: 2022/08/21 10:22:15 by pdursley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	check_key(char c)
{
	if (c == '\0')
		return (0);
	if ((c >= 33 && c <= 45) || (c == 46) || (c == 64) || (c == 91) \
			|| (c >= 92 && c <= 94) || (c == 96) || (c >= 123 && c <= 126))
		return (1);
	return (-1);
}

char	*parse_while(char *res, char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != 61)
	{
		if (check_key(s[i]) == 0)
			break ;
		if (s[i] == 92)
		{
			i ++;
			continue ;
		}
		res[j] = s[i];
		i ++;
		j ++;
	}
	return (res);
}

char	*parse_inf_key(char *s)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	while (s[i] != 61)
	{
		if (check_key(s[i]) == 0)
			break ;
		if (s[i] == 92)
		{
			i ++;
			continue ;
		}
		i ++;
		j ++;
	}
	res = (char *)malloc(j + 1);
	if (!res)
		exit_ms("error malloc", -1);
	res[j] = 0;
	return (parse_while(res, s));
}

char	*val_malloc(char *s, char *res)
{
	if (*s == 61 && !(*s + 1))
		return (one_c(res, 2));
	s ++;
	res = ft_strdup(s);
	return (res);
}

char	*parse_inf_val(char *s)
{
	char	*res;

	res = 0;
	while (*s != 61)
	{
		if (*s == '\0')
			return (one_c(res, 1));
		s ++;
	}
	res = val_malloc(s, res);
	return (res);
}
