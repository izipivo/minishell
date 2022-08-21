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

t_env	*make_env_list(char **envp)
{
	int		i;
	void	*tmp;
	t_env	*lenv;

	i = 0;
	if (!envp)
		exit(1);
	lenv = malloc(sizeof(t_env));
	if (i == 0)
		tmp = lenv;
	lenv->key = parse_inf_key(envp[i]);
	lenv->val = parse_inf_val(envp[i]);
	while (envp[++ i])
	{
		lenv->next = malloc(sizeof(t_env));
		if (!lenv)
			exit(1);
		lenv = lenv->next;
		lenv->key = parse_inf_key(envp[i]);
		lenv->val = parse_inf_val(envp[i]);
	}
	lenv->next = 0;
	return (tmp);
}

void	*free_lenv(t_env *lenv)
{
	void	*tmp;

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
		tmp = lenv;
		lenv = lenv->next;
		free(tmp);
	}
	return (NULL);
}
