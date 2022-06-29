/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 15:32:12 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/12 15:14:55 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_mshell	inf;

static void	dollar_start(char *val, char **buff, int *ii)
{
	int		i;
	char	*buf;

	i = *ii;
	buf = *buff;
	while (val[++i] && val[i] != '$')
		;
	buf[i--] = 0;
	while (val[++i] && val[i] == '$')
	{
		if (!val[i + 1])
		{
			strapp(&buf, "$", 1);
		}
		else if (val[i + 1] == '$')
		{
			strapp(&buf, "1488", 1);
			++i;
		}
		else if (val[i + 1] == '?')
		{
			strapp(&buf, "228", 1);
			++i;
		}
	}
	*ii = i;
}

void	check_dlr(t_list *token)
{
	char	*buf;
	char	*remainig;
	int		i;
	int		last_char;

	i = -1;
	remainig = NULL;
	buf = ft_strdup(token->val);
	if (!buf)
		exit_ms("malloc rip!", 1);
	dollar_start(token->val, &buf, &i);
	last_char = get_last_char_of_dlr(&token->val[i], token);
	if (last_char + i <= (int)ft_strlen(token->val))
	{
		remainig = ft_strdup(&token->val[i + last_char]);
		if (!remainig)
			exit_ms("malloc rip", 1);
	}
	token->val[i + last_char] = 0;
	strapp(&buf, find_env(&token->val[i]), 2);
	if (remainig)
		strapp(&buf, remainig, 2);
	free(token->val);
	token->val = buf;
}

t_pipes	*stop_exec(t_pipes *new)
{
	if (new)
	{
		free(new[0].cmd);
		free(new);
	}
	inf.tokens = free_tokens(inf.tokens);
	return (NULL);
}

t_pipes	*end_pipes(t_pipes *new, int i, int j)
{
	cap(new, i, ++j);
	if (i == -1)
	{
		free(new);
		new = NULL;
	}
	else
		new[i].next = NULL;
	inf.tokens = free_tokens(inf.tokens);
	return (del(new));
}
