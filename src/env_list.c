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

#include "../includes/minishell.h"

int	ft_arrlen(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		;
	return (i);
}
/*
void	freearr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr[i]);
	arr[i] = NULL;
	free(arr);
	arr = NULL;
}

char	*ft_arrcat(char **arr)
{
	int		i;
	char	*cated;
	char	*tmp;

	i = -1;
	if (!arr || !arr[0])
		return (NULL);
	cated = ft_strdup(arr[0]);
	if (ft_arrlen(arr) == 1)
	{
		printf("gg\n");
		return (cated);
	}
	while (arr[++i])
	{
		if (arr[i + 1])
		{
			tmp = cated;
			cated = ft_strjoin(cated, arr[i + 1]);
			free(tmp);
		}
	}
	tmp = ft_strjoin("'", cated);
	free(cated);
	cated = tmp;
	tmp = ft_strjoin(cated, "'");
	free(cated);
	return (tmp);
}*/

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
		//printf("%s=%s\n", lenv[i].key, lenv[i].val);
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
