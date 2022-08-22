/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dolar2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 15:32:12 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/12 15:14:55 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

extern t_mshell	g_inf;

t_list	*newlst(char *val, int start, int end, char *str)
{
	t_list	*elem;

	elem = (t_list *) malloc(sizeof(t_list));
	if (!elem)
		return (0);
	elem->next = NULL;
	if (str)
	{
		elem->val = str;
		return (elem);
	}
	elem->val = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!elem->val)
		exit_ms("malloc rip", 1);
	ft_strlcpy(elem->val, &val[start], end - start + 1);
	return (elem);
}

int	isdollar(char *line, int i)
{
	if (i - 1 && line[i - 2] == '$' && ft_isdigit(line[i - 1]))
		return (0);
	if (line[i] == '?' && i && line[i - 1] == '$')
		return (1);
	if ((ft_isalnum(line[i]) && i && line[i - 1] != '?') || line[i] == '_'
		|| (line[i] == '$' && i && line[i - 1] == '$'))
		return (1);
	return (0);
}

static char	*extra_dolar(char *line, int start, char *str, int end)
{
	str = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!str)
		exit_ms("malloc rip", 1);
	ft_strlcpy(str, &line[start], end - start + 2);
	return (find_env(str));
}

char	*replace_dollar(char *line, int start, int end)
{
	char	*str;
	int		i;

	str = NULL;
	i = -2;
	if (line[start] == '?')
		return (ft_itoa(g_inf.code));
	if (start == end + 1)
	{
		str = ft_strdup("$");
		if (!str)
			exit_ms("malloc_rip", 1);
		return (str);
	}
	if (line[start] == '$')
	{
		while (++i < (end - start + 2) / 2)
			strapp(&str, "228", 1);
		if ((end - start + 2) % 2)
			strapp(&str, "$", 1);
		return (str);
	}
	return (extra_dolar(line, start, str, end));
}

char	*joinlist(t_list **bl)
{
	char	*str;
	t_list	*elem;
	t_list	*tmp;

	str = NULL;
	elem = *bl;
	while (elem)
	{
		tmp = elem;
		strapp(&str, elem->val, 2);
		elem = elem->next;
		free(tmp);
	}
	free(bl);
	return (str);
}
