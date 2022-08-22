/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 15:32:12 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/12 15:14:55 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mshell	g_inf;

static char	**copy_envp(char **envp)
{
	char	**copy;
	int		i;

	i = -1;
	copy = (char **)malloc(sizeof(char *) * (str_len(envp) + 1));
	if (!copy)
		exit_ms("malloc rip!", EXIT_ERROR);
	while (envp[++i])
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
			exit_ms("malloc rip!", EXIT_ERROR);
	}
	copy[i] = NULL;
	return (copy);
}

static void	init(char **envp)
{
	ft_memset(&g_inf, 0, sizeof(t_mshell));
	g_inf.env = copy_envp(envp);
	g_inf.lenv = make_env_list(envp);
	signal(SIGQUIT, sig_quit);
	signal(SIGINT, sig_quit);
}


/*
//		main
*/

#ifdef MAIN

int	main(int argc, char **argv, char **envp)
{
	char	*tmp;

	(void)argc;
	(void)argv;
	init(envp);
	while (3)
	{
		g_inf.line = readline(PROMPT);
		if (g_inf.line == NULL)
			exit_ms("exit", 0);
		if (!ft_strlen(g_inf.line))
		{
			free(g_inf.line);
			continue ;
		}
		add_history(g_inf.line);
		tmp = expand_dol(g_inf.line);
		if (!tmp)
		{
			free(g_inf.line);
			g_inf.line = NULL;
			continue ;
		}
		g_inf.line = tmp;
		g_inf.pipes = parse(g_inf.line, -1, -1);
		free(g_inf.line);
		g_inf.line = NULL;
		g_inf.code = 0;
		if (g_inf.pipes && (g_inf.mask >> 16))
			pipex();
		g_inf.pipes = free_pipes(g_inf.pipes);
		g_inf.mask &= 1 << 3;
	}
}

#endif

#ifdef TEST
/*
//		main для тестера
*/

int     main(int argc, char **argv, char **envp)
{
	char	*tmp;
	(void)argc;
	(void)argv;
	init(envp);

    // if (argc < 3)
	// 	exit(228);
	g_inf.line = ft_strdup(argv[2]);
	if (!g_inf.line || ft_strlen(g_inf.line) == 0)
		exit_ms(NULL, 0);
	// printf("%s\n", g_inf.line);
	if (g_inf.line == NULL)
		exit_ms("exit", 0);

	tmp = expand_dol(g_inf.line);
	if (!tmp)
	{
		free(g_inf.line);
		g_inf.line = NULL;
		return (0);
	}
	g_inf.line = tmp;
	g_inf.pipes = parse(g_inf.line, -1, -1);
	free(g_inf.line);
	g_inf.line = NULL;
	if (g_inf.pipes && (g_inf.mask >> 16))
		pipex();
	g_inf.pipes = free_pipes(g_inf.pipes);
	g_inf.mask = 0;
	return (g_inf.code);
}
#endif

#ifdef GDB
/*
//		main для gdb
*/
int     main(int argc, char **argv, char **envp)
{
	char	*tmp;
	(void)argc;
	(void)argv;
	init(envp);

	g_inf.line = ft_strdup("ls -la > tmp/file");
	if (!g_inf.line || ft_strlen(g_inf.line) == 0)
		exit_ms(NULL, 0);
	// printf("%s\n", g_inf.line);
	if (g_inf.line == NULL)
		exit_ms("exit", 0);

	tmp = expand_dol(g_inf.line);
	if (!tmp)
	{
		free(g_inf.line);
		g_inf.line = NULL;
		return (0);
	}
	g_inf.line = tmp;
	g_inf.pipes = parse(g_inf.line, -1, -1);
	free(g_inf.line);
	g_inf.line = NULL;
	if (g_inf.pipes && (g_inf.mask >> 16))
		pipex();
	g_inf.pipes = free_pipes(g_inf.pipes);
	g_inf.mask = 0;
	return (g_inf.code);
}
#endif
