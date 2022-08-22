/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdursley <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:21:12 by pdursley          #+#    #+#             */
/*   Updated: 2022/08/21 10:22:15 by pdursley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

extern t_mshell	g_inf;

void	print_env(void)
{
	void	*tmp;

	tmp = g_inf.lenv;
	while (g_inf.lenv)
	{
		ft_putstr_fd(g_inf.lenv->key, 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd(g_inf.lenv->val, 1);
		ft_putchar_fd('\n', 1);
		g_inf.lenv = g_inf.lenv->next;
	}
	g_inf.lenv = tmp;
}

int	env_main(int index)
{
	int	i;

	i = -1;
	while (g_inf.pipes[index].cmd[++ i])
		;
	if (i != 1)
	{
		ft_putstr_fd("env: ", 2);
		ft_putchar_fd('\'', 2);
		ft_putstr_fd(g_inf.pipes[index].cmd[1], 2);
		ft_putchar_fd('\'', 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	print_env();
	return (0);
}
