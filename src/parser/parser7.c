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

int	tok_quant(char *line)
{
	char	key;
	int		count;
	int		i;

	count = 19;
	i = 0 ;
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
	inf.tokens[*token_index].key = key;
	inf.tokens[*token_index].val = (char *)malloc(sizeof(char) * 1000);
	if (!inf.tokens[*token_index].val)
		exit_ms("malloc", 1);
}