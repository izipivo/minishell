/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdursley <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:21:12 by pdursley          #+#    #+#             */
/*   Updated: 2022/08/21 10:22:15 by pdursley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

extern t_mshell	g_inf;

void	sort_env(t_mshell	*g_inf)
{
	char	**exp;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	exp = ft_exp(g_inf);
	while (exp[i])
	{
		j = i + 1;
		while (exp[j])
		{
			if (ft_strncmp(exp[i], exp[j], ft_strlen_env(exp[j])) > 0)
			{
				tmp = exp[i];
				exp[i] = exp[j];
				exp[j] = tmp;
			}
			j ++;
		}
		i ++;
	}
	print_exp(exp);
	free_exp(exp);
}

void	error_print(char *str, int i)
{
	if (str[i] == 33)
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
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
}

int	check_pipes_cmd(char *str)
{
	int	i;

	i = 0;
	if (str[i] >= '0' && str[i] <= '9')
		return (1);
	while (str[i])
	{
		if (str[0] == 61 || (str[0] == ' ' && str[1] == 61))
			return (1);
		if (str[i] == 43 && str[i + 1] == 61)
		{
			++ i;
			break ;
		}
		if (str[0] == 45)
			return (2);
		if ((check_key(str[i])) == 1)
		{
			error_print(str, i);
			return (1);
		}
		i ++;
	}
	return (-1);
}

char	**back_cmd(char **cmd, char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		free(cmd[i]);
		cmd[i] = ft_strdup(tmp[i]);
		i ++;
	}
	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i ++;
	}
	free(tmp);
	return (cmd);
}

int	export_main(int index)
{
	int		i;
	int		flag;

	flag = 0;
	i = 0;
	ft_check(index);
	while (g_inf.pipes[index].cmd[i])
	{
		flag = check_pipes_cmd(g_inf.pipes[index].cmd[i]);
		if (flag == 1)
			return (1);
		if (flag == 2)
			return (2);
		else if (flag == 2)
		{
			i = 0;
			continue ;
		}
		i ++;
	}
	ft_run(i, index);
	return (0);
}
