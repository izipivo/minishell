/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 12:12:31 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/29 12:12:33 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_mshell	inf;

void	free_val(t_list *token)
{
	if (token && token->val)
	{
		free(token->val);
		token->val = NULL;
	}
}

void	print_list(t_list *tokens)
{
	while (tokens)
	{
		printf("key: %d, val: %s\n", tokens->key, tokens->val);
		tokens = tokens->next;
	}
}

int	token_key(char line)
{
	if (line == '|')
		return (PIPE);
	else if ((line >= 9 && line <= 13) || line == 32)
		return (SPC);
	else if (line == '"')
		return (DQUOTES);
	else if (line == 39)
		return (SQUOTES);
	else if (line == '$')
		return (DOLLAR);
	else if (line == '<')
		return (INFILE);
	else if (line == '>')
		return (OUTFILE);
	else
		return (COMMAND);
}
