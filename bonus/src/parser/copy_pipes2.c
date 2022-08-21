/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 15:32:12 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/12 15:14:55 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cap(t_pipes *new, int i, int j)
{
	new[i].cmd[j] = NULL;
	if (i)
	{
		new[i - 1].next = &new[i];
	}
}

void	copy_out(t_pipes *new, char *val, char key)
{
	if (new->out)
		free(new->out);
	new->out = ft_strdup(val);
	if (!new->out)
		exit_ms("malloc rip", 1);
	new->mask |= key % 2 << 1;
}

static char	*help(t_list *token)
{
	t_list	*tmp;

	tmp = token->prev;
	while (tmp && tmp->key == SPC)
		tmp = tmp->prev;
	if (tmp && tmp->key == COMMAND)
		return (ft_strdup(" "));
	else
		return (NULL);
}

static void	help2(t_list *token)
{
	char	*buf;

	token->val[ft_strlen(token->val) - 1] = 0;
	buf = ft_strdup(&token->val[1]);
	free(token->val);
	token->val = buf;
}

void	remove_quotes(t_list *token)
{
	while (token)
	{
		if (token->key == SQUOTES || token->key == DQUOTES)
		{
			token->key = COMMAND;
			if (ft_strlen(token->val) < 3)
			{
				free(token->val);
				while (token->next && token->next->key == SPC)
					token->next = token->next->next;
				if (token->next && token->next->key == COMMAND)
				{
					strapp2(" ", &token->next->val);
					token->val = NULL;
				}
				else
					token->val = help(token);
				token = token->next;
				continue ;
			}
			help2(token);
		}
		token = token->next;
	}
}
