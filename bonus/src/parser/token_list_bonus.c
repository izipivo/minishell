/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 15:32:12 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/12 15:14:55 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

extern t_mshell	g_inf;

void	*free_tokens(t_list *token)
{
	int		i;

	i = -1;
	while (&token[++i] != g_inf.end_of_tokens)
	{
		if (token[i].val != NULL)
			free_val(&(token[i]));
	}
	free(token);
	return (NULL);
}

int	q_args(t_list *token)
{
	int	count;

	count = 1;
	if (token->key == PIPE)
		token = token->next;
	while (token && token->key != PIPE)
	{
		if (token->key == COMMAND)
			count++;
		token = token->next;
	}
	return (count);
}

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
	else if (line == '<')
		return (INFILE);
	else if (line == '>')
		return (OUTFILE);
	else
		return (COMMAND);
}
