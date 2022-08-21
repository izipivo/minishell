/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdursley <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:21:12 by pdursley          #+#    #+#             */
/*   Updated: 2022/08/21 10:22:15 by pdursley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_mshell	g_inf;

void	del_unset(t_env *prev)
{
	t_env	*lenv;

	lenv = prev->next;
	prev->next = lenv->next;
	free(lenv->key);
	free(lenv->val);
	free(lenv);
}

void	error_print_unset(char *str, int i)
{
	if (str[i] == 45)
		return ;
	if (str[i] == 33 || str[i] == 59)
	{
		ft_putstr_fd("minishell: ", 2);
		while (str[i])
		{
			write(2, &str[i], 1);
			i ++;
		}
		ft_putstr_fd(": event not found\n", 2);
	}
	else
		return ;
}

int	check_pipes_cmd_unset(char *str)
{
	int	i;

	i = -1;
	if (str[0] >= '0' && str[0] <= '9')
		return (0);
	while (str[++ i])
	{
		if (str[i] == 59)
			return (127);
		if (str[i] == 61)
			return (0);
	}
	i = 0;
	while (str[i])
	{
		if (str[0] == 45)
			return (2);
		if ((check_key(str[i])) == 1)
		{
			error_print_unset(str, i);
			return (0);
		}
		i ++;
	}
	return (-1);
}

int	unset_main(int index)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	g_inf.mask |= 1 << 3;
	while (g_inf.pipes[index].cmd[i])
	{
		flag = check_pipes_cmd_unset(g_inf.pipes[index].cmd[i]);
		if (flag == 0)
			return (1);
		if (flag == 2)
			return (2);
		if (flag == 127)
			return (127);
		i ++;
	}
	if (i == 1)
		return (0);
	unset_env_list(g_inf.lenv, g_inf.pipes[index].cmd);
	if (!g_inf.lenv)
		return (0);
	return (0);
}
