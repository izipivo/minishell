/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 15:32:12 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/12 15:14:55 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_mshell	g_inf;

static void	joining_commands(t_list *token, char *buf, t_list *cpy)
{
	int		f;

	f = 0;
	buf = token->val;
	cpy = token->next;
	while (cpy && cpy->key == COMMAND)
	{
		strapp(&buf, cpy->val, 2);
		cpy->val = 0;
		cpy = cpy->next;
		f = 1;
	}
	if (f)
	{
		token->val = buf;
		token->next = cpy;
		f = 0;
	}
}

int	join_commands(t_list *token)
{
	char	*buf;
	t_list	*cpy;

	buf = NULL;
	cpy = NULL;
	while (token)
	{
		if (token->key == COMMAND)
			joining_commands(token, buf, cpy);
		token = token->next;
	}
	return (0);
}

t_pipes	*remalloc(void)
{
	t_list	*old;
	t_pipes	*new;

	old = g_inf.tokens;
	g_inf.mask = count_pipes(old) << 16;
	new = (t_pipes *) malloc(sizeof(t_pipes) * ((g_inf.mask >> 16) + 1));
	if (!new)
		exit_ms("malloc rip", 1);
	ft_memset(&new[0], 0, sizeof(t_pipes));
	new[0].cmd = (char **) malloc(sizeof(char *) * q_args(old));
	if (!new[0].cmd)
		exit_ms("malloc rip", 1);
	return (copy_pipes(new, old));
}

void	strapp(char **s1, char *s2, int f)
{
	char	*str;

	str = *s1;
	if (!str && !s2)
		return ;
	if (!str)
	{
		*s1 = ft_strdup(s2);
	}
	else if (s2)
	{
		*s1 = ft_strjoin(str, s2);
		if (f)
		{
			free(str);
			str = NULL;
		}
	}
	if (f == 2)
	{
		free(s2);
		s2 = NULL;
	}
	if (!(*s1))
		exit_ms("malloc", 1);
}

void	strapp2(char *str, char **s2)
{
	char	*tmp;

	tmp = ft_strjoin(str, *s2);
	if (!tmp)
		exit_ms("malloc rip", 1);
	free(*s2);
	*s2 = tmp;
	ft_putendl_fd(*s2, 2);
}
