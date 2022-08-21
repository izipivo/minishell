/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 15:32:12 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/12 15:14:55 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_mshell	g_inf;

static void	proof(t_list *token)
{
	if ((token->key == OUTFILE || token->key == INFILE)
		&& ft_strlen(token->val) > 2)
		exit_ms("parser error near '>'", 2);
	if (token->key == OUTFILE && ft_strlen(token->val) == 2)
		token->key = APPEND;
	else if (token->key == INFILE && ft_strlen(token->val) == 2)
		token->key = HEREDOC;
}

void	check_redirs(t_list *token)
{
	while (token)
	{
		proof(token);
		if (token->key > 2 && token->key < 7)
		{
			if (!token->next)
				exit_ms("syntax error near unexpected token", 2);
			while (token->next && token->next->key == SPC)
			{
				token->next = token->next->next;
			}
			if (!token->next || token->next->key != COMMAND)
				exit_ms("not valid syntax!", 1);
			free(token->val);
			token->val = ft_strdup(token->next->val);
			free(token->next->val);
			token->next->val = NULL;
			token->next = token->next->next;
		}
		else if (token->key == SQUOTES || token->key == DQUOTES)
			token->key = COMMAND;
		token = token->next;
	}
}

void	check_wildcards(t_list *tokens)
{
	char	*tmp;

	while (tokens)
	{
		if (tokens->key == COMMAND && ft_strchr(tokens->val, '*') != NULL)
		{
			tmp = tokens->val;
			tokens->val = find_wildcard_word(ft_split(tokens->val,
						' '));
			free(tmp);
		}
		tokens = tokens->next;
	}
}
