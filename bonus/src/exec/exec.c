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
		if (token->val && !count)
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
	if (g_inf.env)
		g_inf.env = free_env(g_inf.env);
	rl_clear_history();
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
	if (sig == SIGINT || sig == SIGQUIT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
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
	if (g_inf.env)
		g_inf.env = free_env(g_inf.env);
	if (status >= 0)
		exit(status);
	exit(1);
}

int	return_prompt(char *err, int status)
{
	ft_putendl_fd(err, 2);
	g_inf.code = status;
	return (RETURN_PROMPT);
}
