/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   same_for_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdursley <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:21:12 by pdursley          #+#    #+#             */
/*   Updated: 2022/08/21 10:22:15 by pdursley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

extern t_mshell	g_inf;

char	**new_key(char **cmd)
{
	int		i;
	char	**str;

	i = 0;
	while (cmd[i])
		i ++;
	str = (char **)malloc(sizeof(char *) * (i + 1));
	if (!str)
		exit_ms("error malloc", -1);
	str[i] = 0;
	i = 0;
	while (cmd[i])
	{
		str[i] = ft_strdup(cmd[i]);
		i ++;
	}
	i = 0;
	return (str);
}

int	same_key(void)
{
	int		i;
	void	*tmp;

	tmp = g_inf.lenv;
	while (g_inf.lenv)
	{
		i = 1;
		while (g_inf.pipes[0].cmd[i])
		{
			if (!(ft_strncmp(g_inf.lenv->key, \
				g_inf.pipes[0].cmd[i], ft_strlen(g_inf.lenv->key))))
			{
				g_inf.lenv = tmp;
				return (-1);
			}
			else
				i ++;
		}
		g_inf.lenv = g_inf.lenv->next;
	}
	g_inf.lenv = tmp;
	return (1);
}
