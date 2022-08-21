/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_func_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdursley <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:21:12 by pdursley          #+#    #+#             */
/*   Updated: 2022/08/21 10:22:15 by pdursley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_mshell	g_inf;

char	**ft_join_res(char **result, char	*tmp_del, int i)
{
	result[i] = ft_strjoin(result[i], "=");
	free(tmp_del);
	tmp_del = result[i];
	result[i] = ft_strjoin(result[i], "\"");
	free(tmp_del);
	tmp_del = result[i];
	result[i] = ft_strjoin(result[i], g_inf.lenv->val);
	free(tmp_del);
	tmp_del = result[i];
	result[i] = ft_strjoin(result[i], "\"");
	free(tmp_del);
	return (result);
}

char	**join_env(t_mshell *g_inf, char **result, int i)
{
	char	*tmp_del;

	while ((unsigned long) i != (unsigned long) -1)
	{
		result[i] = ft_strdup(g_inf->lenv->key);
		tmp_del = result[i];
		if (g_inf->lenv->val[0] == '\0')
		{
			i --;
			g_inf->lenv = g_inf->lenv->next;
			continue ;
		}
		if (g_inf->lenv->val[0] == '=' && g_inf->lenv->val[1] == '\0')
		{
			result[i] = ft_strjoin(result[i], "=");
			free(tmp_del);
			i --;
			g_inf->lenv = g_inf->lenv->next;
			continue ;
		}
		result = ft_join_res(result, tmp_del, i);
		i --;
		g_inf->lenv = g_inf->lenv->next;
	}
	return (result);
}

char	**ft_exp(t_mshell	*g_inf)
{
	int		i;
	char	**result;
	void	*tmp;

	i = 0;
	tmp = g_inf->lenv;
	while (g_inf->lenv)
	{
		i ++;
		g_inf->lenv = g_inf->lenv->next;
	}
	g_inf->lenv = tmp;
	result = (char **)malloc(sizeof(char *) * (i + 1));
	if (!result)
		exit_ms("error malloc", -1);
	result[i] = 0;
	i --;
	result = join_env(g_inf, result, i);
	g_inf->lenv = tmp;
	return (result);
}
