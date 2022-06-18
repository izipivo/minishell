/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdpwdechoexit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:37:50 by sdonny            #+#    #+#             */
/*   Updated: 2022/04/26 15:18:46 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 *		!!! echo $... !!!
 */

void	ft_echo(char **string, int n)
{
	int num;

	num = 1;
	while (string[num])
	{
		ft_putstr_fd(string[num], 1);
		if (string[++ num])
			ft_putchar_fd(' ', 1);
	}
	if (!n)
		ft_putchar_fd('\n', 1);
}

extern t_mshell inf;

void echo_main(void)
{
	int	f;
	int	i;

	i = 0;
	f = 0;
	while (inf.pipes[0].cmd[i])
		i ++;
	if (i == 1)
	{
		ft_putchar_fd('\n', 2);
		return ;
	}
	i = -1;
	while (!ft_strncmp(inf.pipes[0].cmd[++ i], "-n", 2))
		f = 1;
	ft_echo(inf.pipes[0].cmd, f);
	return ;
}
