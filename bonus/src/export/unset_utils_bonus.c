/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdursley <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:21:12 by pdursley          #+#    #+#             */
/*   Updated: 2022/08/21 10:22:15 by pdursley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

extern t_mshell	g_inf;

void	ft_del(char **del, int i)
{
	void	*tmp;

	if (!ft_strncmp(g_inf.lenv->key, del[i], ft_strlen(g_inf.lenv->key)))
	{
		tmp = g_inf.lenv->next;
		free(g_inf.lenv->key);
		free(g_inf.lenv->val);
		free(g_inf.lenv);
		g_inf.lenv = tmp;
	}
}

void	unset_env_list(t_env *lenv, char **del)
{
	int		i;
	void	*tmp;

	i = 0;
	while (del[i])
	{
		ft_del(del, i);
		++i;
	}
	tmp = NULL;
	while (lenv)
	{
		i = -1;
		while (del[++ i])
		{
			if (!ft_strncmp(lenv->key, del[i], ft_strlen(lenv->key)))
			{
				lenv = lenv->next;
				del_unset(tmp);
			}
		}
		tmp = lenv;
		if (lenv)
			lenv = lenv->next;
	}
}
