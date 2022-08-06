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

char	*find_env(char *find)
{
	t_env	*lenv;
	char	*found;

	lenv = g_inf.lenv;
	while (lenv)
	{
		if (!ft_strncmp(lenv->key, find, ft_strlen(find)))
		{
			found = ft_strdup(lenv->val);
			if (!found)
				exit_ms(NULL, 1);
			free(find);
			return (found);
		}
		lenv = lenv->next;
	}
	free(find);
	return (NULL);
}

static void	check_redirs(void)
{
	t_list	*token;

	token = g_inf.tokens;
	while (token)
	{
		if ((token->key == OUTFILE || token->key == INFILE)
			&& ft_strlen(token->val) > 2)
			exit_ms("parser error near '>'", 2);
		if (token->key == OUTFILE && ft_strlen(token->val) == 2)
			token->key = APPEND;
		else if (token->key == INFILE && ft_strlen(token->val) == 2)
			token->key = HEREDOC;
		if (token->key > 2 && token->key < 7)
		{
			if (!token->next)
				exit_ms("syntax error near unexpected token", 2);
			free(token->val);
			token->val = ft_strdup(token->next->val);
			token->next = token->next->next;
		}
		else if (token->key == SQUOTES || token->key == DQUOTES)
			token->key = COMMAND;
		token = token->next;
	}
}

void	check_pipes(t_list *token)
{
	char	check;

	while (token)
	{
		check = PIPE_KO;
		while (token && token->key != PIPE)
		{
			if (token->key == COMMAND)
			{
				check = PIPE_OK;
			}
			token = token->next;
		}
		if (check == PIPE_KO)
			exit_ms("wrong syntax!", EXIT_ERROR);
		if (token)
			token = token->next;
	}
}

//t_pipes	*cleaning(void)
//{
//	if (g_inf.tokens->key == PIPE)
//		exit_ms("syntax error near unexpected token `|'", 2);
////	print_list(g_inf.tokens);
//// printf("_______________________\n");
//	if (QUOTS(g_inf.mask))
//	{
//		remove_quotes(g_inf.tokens);
//// print_list(g_inf.tokens);
//// printf("_______________________\n");
//	}
//	check_redirs();
//	check_pipes(g_inf.tokens);
//// print_list(g_inf.tokens);
//// ft_putstr_fd("_______________________\n",1);
//	join_commands(g_inf.tokens);
//// print_list(g_inf.tokens);
//// ft_putstr_fd("_______________________\n",1);
//	return (remalloc());
//}
t_pipes	*cleaning(void)
{
	if (g_inf.tokens->key == PIPE)
		exit_ms("syntax error near unexpected token `|'", 2);
	if (QUOTS(g_inf.mask))
	{
		remove_quotes(g_inf.tokens);
	}
	check_redirs();
	check_pipes(g_inf.tokens);
	join_commands(g_inf.tokens);
	return (remalloc());
}

int	same_token(char old, char new)
{
	char	key;

	key = token_key(new);
	if (key == SQUOTES || key == DQUOTES)
		g_inf.mask |= 1 << 1;
	if ((old == DQUOTES || old == SQUOTES) && old == key)
		return (-1);
	if (old != key && (old == SQUOTES || old == DQUOTES))
		return (1);
	if (old == key)
		return (1);
	return (0);
}
