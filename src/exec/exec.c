/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:58:59 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/11 15:36:27 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_mshell	g_inf;

int	count_pipes(t_list *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->key == COMMAND && token->val && !count)
			++count;
		else if (count && token->key == PIPE)
			++count;
		token = token->next;
	}
	return (count);
}

void	sig_hand(int sig)
{
	sig_quit(0);
	if (g_inf.tokens)
		g_inf.tokens = free_tokens(g_inf.tokens);
	if (g_inf.lenv)
		g_inf.lenv = free_lenv(g_inf.lenv);
	if (g_inf.pipes)
		g_inf.pipes = free_pipes(g_inf.pipes);
	ft_putendl_fd("\nbye", 1);
	exit(sig);
}

void	sig_quit(int sig)
{
	int	i;

	i = -1;
	if (g_inf.pids)
	{
		while (++i < (g_inf.mask >> 16))
		{
			if (g_inf.pids[i])
			{
				if (sig == SIGINT)
					kill(g_inf.pids[i], SIGKILL);
				else
					kill(g_inf.pids[i], SIGQUIT);
				g_inf.pids[i] = 0;
			}
		}
	}
	else if (sig == SIGQUIT)
	{
		rl_redisplay();
		return ;
	}
	g_inf.code = 128 + sig;
}

void	exit_ms(char *err, int status)
{
	ft_putendl_fd(err, 2);
	sig_quit(0);
	if (g_inf.line)
		free(g_inf.line);
	if (g_inf.tokens)
		g_inf.tokens = free_tokens(g_inf.tokens);
	if (g_inf.lenv)
		g_inf.lenv = free_lenv(g_inf.lenv);
	if (g_inf.pipes)
		g_inf.pipes = free_pipes(g_inf.pipes);
	if (status >= 0)
		exit(status);
	rl_clear_history();
	exit(1);
}
