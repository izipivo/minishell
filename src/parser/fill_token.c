/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 15:32:12 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/12 15:14:55 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_mshell	g_inf;

int	tok_quant(char *line)
{
	char	key;
	int		count;
	int		i;

	count = 19;
	i = -1;
	key = 64;
	while (line[++i])
	{
		if (same_token(key, line[i]) == 1)
			continue ;
		else if (same_token(key, line[i]) == -1)
		{
			key = 88;
			continue ;
		}
		++count;
		key = token_key(line[i]);
	}
	return (count);
}

void	make_new_token(int *token_index, int *val_index, char key)
{
	*val_index = 0;
	++(*token_index);
	g_inf.tokens[*token_index].key = key;
	g_inf.tokens[*token_index].val = (char *)malloc(sizeof(char)
			* g_inf.line_len);
	if (!g_inf.tokens[*token_index].val)
		exit_ms("malloc", 1);
}

static int	fill_token2(int old, int *val_index, int key, int *token_index)
{
	if (old != 88 && old != 64)
		g_inf.tokens[*token_index].val[*val_index + 1] = 0;
	if (old != 64)
	{
		g_inf.tokens[*token_index].next = &g_inf.tokens[*token_index + 1];
		g_inf.tokens[*token_index + 1].prev = &g_inf.tokens[*token_index];
	}
	make_new_token(token_index, val_index, key);
	return (*token_index);
}

int	fill_token(int old, char new, int *token_index, int *val_index)
{
	int	key;
	int	st;

	key = token_key(new);
	st = same_token(old, new);
	if (st == 1)
	{
		++(*val_index);
		return (*token_index);
	}
	if (st == -1)
	{
		g_inf.tokens[*token_index].val[*val_index + 1] = new;
		g_inf.tokens[*token_index].val[*val_index + 2] = 0;
		*val_index = -1;
		return (*token_index);
	}
	return (fill_token2(old, val_index, key, token_index));
}
