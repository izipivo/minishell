/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dolar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 15:32:12 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/12 15:14:55 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_mshell	g_inf;

static void	ed_init(int *i, int *start, char *dquot, t_list ***bl)
{
	*i = -1;
	*start = 0;
	*dquot = 0;
	*bl = (t_list **)malloc(sizeof(t_list *));
	if (!*bl)
		exit_ms("malloc rip", 1);
	**bl = NULL;
}

static char	*ed_end(int start, t_list **bl, char *line, int i)
{
	if (start != i)
		ft_lstadd_back(bl, newlst(line, start, i, NULL));
	if (!*bl)
	{
		free(bl);
		return (line);
	}
	free(line);
	return (joinlist(bl));
}

static void	dolr(t_list **bl, char *line, int *start, int *i)
{
	ft_lstadd_back(bl, newlst(line, *start, *i, NULL));
	*start = 1 + *i;
	while (line[++(*i)] && isdollar(line, *i))
		;
	ft_lstadd_back(bl, newlst(line, 0, 0, replace_dollar(line, *start,
				*i - 1)));
	*start = (*i)--;
}

char	*expand_dol(char *line)
{
	t_list	**bl;
	char	dquot;
	int		i;
	int		start;

	ed_init(&i, &start, &dquot, &bl);
	while (line[++i])
	{
		if (line[i] == '"')
			dquot = dquot - 1;
		else if (line[i] == '\'' && !dquot)
		{
			while (line[++i] && line[i] != '\'')
				;
			if (!line[i])
			{
				free_list(bl);
				return_prompt("not closed quote", 1);
				return (NULL);
			}
		}
		else if (line[i] == '$')
			dolr(bl, line, &start, &i);
	}
	return (ed_end(start, bl, line, i));
}
