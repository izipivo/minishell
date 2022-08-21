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

extern t_mshell	g_inf;

void	copy_in(t_pipes *new, char *val, char key)
{
	if (new->in)
		free(new->in);
	new->in = ft_strdup(val);
	if (!new->in)
		exit_ms("malloc rip", 1);
	new->mask |= key % 2;
}

int	copy_word(t_pipes *new, int j, t_list *old)
{
	if (!old->val)
		new->cmd[++j] = ft_strdup(" ");
	else if (old->val)
		new->cmd[++j] = ft_strdup(old->val);
	else
		return (0);
	if (!new->cmd[j])
		exit_ms("malloc rip", 1);
	return (1);
}

t_pipes	*del(t_pipes *new)
{
	int	i;

	i = -1;
	while (1)
	{
		if (!new[++i].cmd[0])
		{
			if (i)
				new[i - 1].next = new[i].next;
		}
		if (new[i].next == NULL)
			break ;
	}
	return (new);
}

void	iter(t_list *old, t_pipes *new, int *i, int *j)
{
	if (old->key == PIPE)
	{
		cap(new, *i, ++(*j));
		ft_memset(&new[++(*i)], 0, sizeof(t_pipes));
		new[*i].cmd = (char **) malloc(sizeof(char *) * q_args(old));
		if (!q_args(old) && new->cmd)
			exit_ms("malloc rip", 1);
		*j = -1;
	}
	else if (old->key > 2 && old->key < 5)
		copy_in(&new[*i], old->val, old->key);
	else if (old->key > 4 && old->key < 7)
		copy_out(&new[*i], old->val, old->key);
	else if (old->key == COMMAND)
		*j += copy_word(&new[*i], *j, old);
}

t_pipes	*copy_pipes(t_pipes *new, t_list *old)
{
	int		i;
	int		j;

	j = -1;
	i = 0;
	while (old)
	{
		iter(old, new, &i, &j);
		old = old->next;
	}
	cap(new, i, ++j);
	if (i == -1)
	{
		free(new);
		new = NULL;
	}
	else
		new[i].next = NULL;
	g_inf.tokens = free_tokens(g_inf.tokens);
	return (del(new));
}
