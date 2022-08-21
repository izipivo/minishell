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

/*
//		main 
*/

t_mshell	g_inf;

#ifdef MAIN

void	init(char **envp)
{
	ft_memset(&g_inf, 0, sizeof(t_mshell));
	g_inf.env = envp;
	g_inf.lenv = make_env_list(envp);
	signal(SIGQUIT, sig_quit);
	signal(SIGINT, sig_quit);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	init(envp);
	while (1)
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
		g_inf.line = expand_dol(g_inf.line);
		g_inf.pipes = parse(g_inf.line, -1, -1);
		free(g_inf.line);
		g_inf.line = NULL;
		g_inf.code = 0;
		 print_pipes(g_inf.pipes);
		if ((g_inf.mask >> 16))
			pipex();
		g_inf.pipes = free_pipes(g_inf.pipes);
		g_inf.mask = 0;
	}
}

#endif

#ifdef TEST
/*
//		main для тестера
*/

int     main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	ft_memset(&g_inf, 0, sizeof(t_mshell));
	g_inf.env = envp;
	g_inf.lenv = make_env_list(envp);
	signal(SIGQUIT, sig_quit);
	signal(SIGINT, sig_hand);

    if (argc < 3)
		exit(228);
	g_inf.line = ft_strdup(argv[2]);
    if (!g_inf.line || ft_strlen(g_inf.line) == 0)
		exit_ms(NULL, 0);
	// printf("%s\n", g_inf.line);
	if (g_inf.line == NULL)
		exit_ms("exit", 0);
	g_inf.line = expand_dol(g_inf.line);
	// printf("%s\n", g_inf.line);
	g_inf.pipes = parse(g_inf.line, -1, -1);
	free(g_inf.line);
	g_inf.line = NULL;
	// print_pipes(g_inf.pipes);
	if ((g_inf.mask >> 16))
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
	(void)argc;
	(void)argv;
	ft_memset(&g_inf, 0, sizeof(t_mshell));
	g_inf.env = envp;
	g_inf.lenv = make_env_list(envp);
	signal(SIGQUIT, sig_quit);
	signal(SIGINT, sig_hand);

	g_inf.line = ft_strdup("whereis ls | cat -e | cat -e > test");
	if (!g_inf.line || ft_strlen(g_inf.line) == 0)
		exit(0);
	// ft_putendl_fd(g_inf.line, 2);
	if (g_inf.line == NULL)
		exit_ms("exit", 0);
	g_inf.line = expand_dol(g_inf.line);
	// ft_putendl_fd(g_inf.line, 2);
	g_inf.pipes = parse(g_inf.line, -1, -1);
	free(g_inf.line);
	g_inf.line = NULL;
	// print_pipes(g_inf.pipes);
	if ((g_inf.mask >> 16))
		pipex();
	g_inf.pipes = free_pipes(g_inf.pipes);
	g_inf.mask = 0;
	return (g_inf.code);
}
#endif
