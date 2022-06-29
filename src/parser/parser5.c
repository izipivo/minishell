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

static void	check_redirs(void)
{
	t_list	*token;

	token = inf.tokens;
	while (token)
	{
		if (DLR(inf.mask) && (token->key == DQUOTES || token->key == DOLLAR))
			check_dlr(token);
		if (token->key == OUTFILE && ft_strlen(token->val) == 2)
			token->key = APPEND;
		else if (token->key == INFILE && ft_strlen(token->val) == 2)
			token->key = HEREDOC;
		if ((token->key >= 3 && token->key <= 6) && ft_strlen(token->val) > 2)
			exit_ms("parser error near '>'", 1);
		else if ((token->key >= 3 && token->key <= 6) && token->next)
		{
			free(token->val);
			token->val = ft_strdup(token->next->val);
			token->next = token->next->next;
		}
		else if (token->key == DOLLAR || token->key == SQUOTES
			|| token->key == DQUOTES)
			token->key = COMMAND;
		token = token->next;
	}
}

static void	remove_quotes(t_list *token)
{
	char	*buf;

	while (token)
	{
		if (token->key == SQUOTES || token->key == DQUOTES)
		{
			if (ft_strlen(token->val) == 2)
			{
				free(token->val);
				token->val = NULL;
				if (token->prev)
					token->prev->next = token->next;
				token = token->next;
				continue ;
			}
			buf = token->val;
			token->val[ft_strlen(token->val) - 1] = 0;
			token->val = ft_strdup(token->val + 1);
			free(buf);
		}
		token = token->next;
	}
}

t_pipes	*cleaning(void)
{
	print_list(inf.tokens);
	ft_putstr_fd("_______________________\n",1);
	if (QUOTS(inf.mask))
	{
		remove_quotes(inf.tokens);
		// print_list(inf.tokens);
		// ft_putstr_fd("_______________________\n",1);
	}
	check_redirs();
	print_list(inf.tokens);
	ft_putstr_fd("_______________________\n",1);
	join_commands(inf.tokens, 0);
	// print_list(inf.tokens);
	// ft_putstr_fd("_______________________\n",1);
	return (remalloc());
}

static int	same_token2(char old, char new, char key)
{
	if (old == DOLLAR && ft_isdigit(new))
	{
		if (!DIGIT(inf.mask))
		{
			inf.mask |= 1 << 2;
			return (1);
		}
		else
		{
			inf.mask &= ~(1 << 2);
			return (0);
		}
	}
	if (old == DOLLAR && (ft_isalnum(new) || new == '_'))
		return (1);
	if (old == key)
		return (1);
	return (0);
}

int	same_token(char old, char new)
{
	char	key;

	key = token_key(new);
	if (key == SQUOTES || key == DQUOTES)
		inf.mask |= 1 << 1;
	if (key == DOLLAR && old != SQUOTES)
		inf.mask |= 1;
	if ((old == DQUOTES || old == SQUOTES) && old == key)
		return (-1);
	if (old != key && (old == SQUOTES || old == DQUOTES))
		return (1);
	return (same_token2(old, new, key));
}
