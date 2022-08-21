/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdursley <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:21:12 by pdursley          #+#    #+#             */
/*   Updated: 2022/08/21 10:22:15 by pdursley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_mshell	g_inf;

char	*ft_res(char *cmd, char *res)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] == 43 && cmd[i + 1] == 61)
		{
			i ++;
			continue ;
		}
		res[j] = cmd[i];
		i ++;
		j ++;
	}
	res[j] = 0;
	free(cmd);
	return (res);
}

char	*new_pipes_cmd(char *cmd)
{
	int		i;
	char	*res;

	i = 0;
	while (cmd[i])
		i ++;
	res = (char *)malloc(sizeof(char) * i);
	if (!res)
		exit_ms("error malloc", -1);
	i = 0;
	return (ft_res(cmd, res));
}

char	**tmp_cmd(char **cmd, char **tmp)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		cmd[i] = parse_inf_key(tmp[i]);
		i ++;
	}
	return (cmd);
}

void	ft_check(int index)
{
	char	**tmp;

	if (same_key() == -1)
	{
		tmp = new_key(g_inf.pipes[index].cmd);
		g_inf.pipes[index].cmd = tmp_cmd(g_inf.pipes[index].cmd, tmp);
		unset_main(index);
		g_inf.pipes[index].cmd = back_cmd(g_inf.pipes[index].cmd, tmp);
	}
}

int	ft_run(int i, int index)
{
	if (i > 1)
	{
		g_inf.mask |= 1 << 3;
		add_variable(g_inf.lenv, g_inf.pipes[index].cmd);
		return (0);
	}
	sort_env(&g_inf);
	return (-1);
}
