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

char	*find_wildcard_word(char **splt)
{
	char	*joined;
	char	*tmp;
	int		i;

	i = -1;
	joined = NULL;
	if (!splt)
		return (NULL);
	while (splt[++i])
	{
		if (ft_strchr(splt[i], '*'))
		{
			tmp = splt[i];
			splt[i] = wldcrd(splt[i]);
			free(tmp);
		}
		strapp(&joined, splt[i], 2);
	}
	free(splt);
	return (joined);
}

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

int	check_pipes(t_list *token)
{
	char	check;

	while (token)
	{
		check = PIPE_KO;
		while (token && token->key != PIPE)
		{
			if (token->key == COMMAND || (token->key > 2 && token->key < 7))
			{
				check = PIPE_OK;
			}
			token = token->next;
		}
		if (check == PIPE_KO)
			return (return_prompt("wrong syntax!", 2));
		if (token && !token->next && token->key == PIPE)
			return (return_prompt("wrong syntax!", 2));
		if (token)
			token = token->next;
	}
	return (0);
}

t_pipes	*cleaning(void)
{
	if (g_inf.tokens->key == PIPE)
	{
		return_prompt("syntax error near unexpected token `|'", 2);
		return (NULL);
	}
	check_wildcards(g_inf.tokens);
	if (g_inf.mask >> 1 & 1)
	{
		remove_quotes(g_inf.tokens);
	}
	if (check_redirs(g_inf.tokens) == RETURN_PROMPT)
		return (NULL);
	if (check_pipes(g_inf.tokens) == RETURN_PROMPT)
		return (NULL);
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
