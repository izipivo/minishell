/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 19:55:33 by sdonny            #+#    #+#             */
/*   Updated: 2022/05/01 19:55:36 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_arrlen(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		;
	return (i);
}

t_env	*make_env_list(char **envp)
{
	int		i;
	char	*sep;
	t_env	*lenv;

	i = -1;
	if (!envp)
		exit(1);
	lenv = (t_env *)malloc(sizeof(t_env) * (ft_arrlen(envp) + 1));
	if (!lenv)
		exit(1);
	while (envp[++i])
	{
		lenv[i].key = ft_strdup(envp[i]);
		sep = ft_strchr(lenv[i].key, 61);
		if (!sep)
		{
			lenv[i].val = NULL;
			continue ;
		}
		lenv[i].val = ft_strdup(sep + 1);
		*sep = '\0';
		if (i > 0)
			lenv[i - 1].next = &lenv[i];
	}
	if (i > 0)
		lenv[i - 1].next = NULL;
	return (lenv);
}

void	*free_lenv(t_env *lenv)
{
	t_env	*bl;

	bl = lenv;
	while (lenv)
	{
		if (lenv->key)
		{
			free(lenv->key);
			lenv->key = NULL;
		}
		if (lenv->val)
		{
			free(lenv->val);
			lenv->val = NULL;
		}
		lenv = lenv->next;
	}
	free(bl);
	bl = NULL;
	return (NULL);
}
