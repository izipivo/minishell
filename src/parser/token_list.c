/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 12:12:22 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/29 12:12:25 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_mshell	inf;

int	is_separator(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ' || c == '&' || c == 39 || c == '"'
		|| c == '<' || c == '>' || c == '(' || c == ')' || c == '|')
		return (1);
	else
		return (0);
}

// int	ft_strapp(char **s1, char *s2)
// {
// 	char	*tmp;

// 	tmp = *s1;
// 	if (!tmp)
// 		*s1 = ft_strdup(s2);
// 	else
// 		*s1 = ft_strjoin(tmp, s2);
// 	if (tmp)
// 	{
// 		free(tmp);
// 		tmp = NULL;
// 	}
// 	if (!*s1)
// 		return (1);					//		malloc_err
// 	return (0);
// }
