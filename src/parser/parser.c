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

int	end_fill_token(int old, char new, int *token_index, int *val_index)
{
	int	key;

	key = token_key(new);
	if (old != 88 && old != 64)
		inf.tokens[*token_index].val[*val_index + 1] = 0;
	if (old != 64)
	{
		inf.tokens[*token_index].next = &inf.tokens[*token_index + 1];
		inf.tokens[*token_index + 1].prev = &inf.tokens[*token_index];
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
		inf.tokens[*token_index].val[*val_index + 1] = new;
		inf.tokens[*token_index].val[*val_index + 2] = 0;
		*val_index = -1;
		return (*token_index);
	}
	return (end_fill_token(old, new, token_index, val_index));
}

void	parse_loop(char *line, int *i, int *n, int *j)
{
	char	key;

	key = 64;
	while (line[++*i])
	{
		if (line[*i] == line[*i + 1] && (line[*i] == '\'' || line[*i] == '"'))
		{
			++*i;
			continue ;
		}
		fill_token(key, line[*i], n, j);
		if (*j == -1)
		{
			key = 88;
			continue ;
		}
		if (!same_token(key, line[*i]))
			key = token_key(line[*i]);
		inf.tokens[*n].val[*j] = line[*i];
	}
}

t_pipes	*parse(char *line)
{
	int		j;
	int		i;
	int		n;

	i = -1;
	n = -1;
	inf.tokens = (t_list *)malloc(sizeof(t_list) * tok_quant(line));
	if (!inf.tokens)
		exit_ms("malloc error", 1);
	parse_loop(line, &i, &n, &j);
	if (j != -1)
		inf.tokens[n].val[++j] = 0;
	inf.tokens[n].next = NULL;
	inf.tokens[0].prev = NULL;
	if ((inf.tokens[n].key == SQUOTES
			|| inf.tokens[n].key == DQUOTES) && j != -1)
		exit_ms("not closed quote", 1);
	return (cleaning());
}

void	free_list(t_list *list)
{
	t_list	*cp;

	cp = list;
	while (list)
	{
		if (list->val)
			free(list->val);
		list->val = NULL;
		list = list->next;
	}
	free(cp);
	cp = NULL;
}
