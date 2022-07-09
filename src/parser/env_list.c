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
	void *tmp;
	t_env	*lenv;

	i = -1;
	if (!envp)
		exit(1);
	lenv = malloc(sizeof(t_env));
	if (i == -1)
		tmp = lenv;
	while (envp[++ i])
	{
		lenv->key = parse_inf_key(envp[i]);
		lenv->val = parse_inf_val(envp[i]);
		lenv->next = malloc(sizeof(t_env));
		if (!lenv)
			exit(1);
		lenv = lenv->next;
	}
	lenv = tmp;
	return (lenv);
}

void	*free_lenv(t_env *lenv)
{
	t_env	*bl;

	bl = lenv;
	while(lenv)
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
