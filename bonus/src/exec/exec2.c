/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:58:59 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/11 15:36:27 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_mshell	g_inf;

void	*free_pipes(t_pipes *pipes)
{
	t_pipes	*cp;
	int		i;

	cp = pipes;
	while (pipes)
	{
		i = -1;
		while (pipes->cmd[++i])
		{
			free(pipes->cmd[i]);
		}
		free(pipes->cmd);
		if (pipes->in)
			free(pipes->in);
		if (pipes->out)
			free(pipes->out);
		pipes = pipes->next;
	}
	free(cp);
	return (NULL);
}

void	print_string(char **str)
{
	int	i;

	i = -1;
	while (str[++i] && *str[i])
	{
		ft_putendl_fd(str[i], 1);
	}
}

void	print_pipes(t_pipes *pipe)
{
	int	i;

	i = -1;
	while (pipe)
	{
		ft_putstr_fd("pipe #", 1);
		ft_putnbr_fd(++i, 1);
		ft_putchar_fd('\n', 1);
		print_string(pipe->cmd);
		printf("input: _%s_\noutput: _%s_\n", pipe->in, pipe->out);
		ft_putstr_fd("_______________________\n", 1);
		pipe = pipe->next;
	}
//	cnt = 1;
}
