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

extern t_mshell	g_inf;

static t_pipes	*cont(int j, int n)
{
	if (j != -1)
		g_inf.tokens[n].val[++j] = 0;
	g_inf.tokens[n].next = NULL;
	g_inf.tokens[0].prev = NULL;
	if ((g_inf.tokens[n].key == SQUOTES || g_inf.tokens[n].key == DQUOTES)
		&& j != -1)
		exit_ms("not closed quote", 1);
	return (cleaning());
}

t_pipes	*parse(char *line, int i, int n)
{
	int		j;
	char	key;

	g_inf.line_len = ft_strlen(line) * 2;
	if (g_inf.line_len < 10)
		g_inf.line_len = 10;
	g_inf.tokens = (t_list *) malloc(sizeof(t_list) * tok_quant(line));
	if (!g_inf.tokens)
		exit_ms("malloc error", 1);
	key = 64;
	while (line[++i])
	{
		fill_token(key, line[i], &n, &j);
		if (j == -1)
			key = 88;
		if (j == -1)
			continue ;
		if (!same_token(key, line[i]))
			key = token_key(line[i]);
		g_inf.tokens[n].val[j] = line[i];
	}
	return (cont(j, n));
}
