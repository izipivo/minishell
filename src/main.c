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

extern t_mshell	inf;

#ifdef MAIN

void	init(char **envp)
{
	ft_memset(&inf, 0, sizeof(t_mshell));
	inf.env = envp;
	inf.lenv = make_env_list(envp);
	signal(SIGQUIT, sig_quit);
	signal(SIGINT, sig_quit);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	init(envp);
	while (3)
	{
		inf.line = readline(PROMPT);
		if (inf.line == NULL)
			exit_ms("exit", 0);
		if (!ft_strlen(inf.line))
		{
			free(inf.line);
			continue ;
		}
		add_history(inf.line);
		inf.line = expand_dol(inf.line);
		inf.pipes = parse(inf.line);
		free(inf.line);
		inf.line = NULL;
		inf.code = 0;
		if (PIPES)
			exec();
		inf.pipes = free_pipes(inf.pipes);
		inf.mask = 0;
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
	ft_memset(&inf, 0, sizeof(t_mshell));
	inf.env = envp;
	inf.lenv = make_env_list(envp);
	signal(SIGQUIT, sig_quit);
	signal(SIGINT, sig_hand);

    if (argc < 3)
        exit(228);
	inf.line = ft_strdup(argv[2]);
    if (!inf.line || ft_strlen(inf.line) == 0)
        exit_ms(NULL, 0);
	// printf("%s\n", inf.line);
	if (inf.line == NULL)
		exit_ms("exit", 0);
	inf.line = expand_dol(inf.line);
	// printf("%s\n", inf.line);
	inf.pipes = parse(inf.line);
	free(inf.line);
	inf.line = NULL;
	// print_pipes(inf.pipes);
	if (PIPES)
		exec();
	inf.pipes = free_pipes(inf.pipes);
	inf.mask = 0;
	return (inf.code);
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
	ft_memset(&inf, 0, sizeof(t_mshell));
	inf.env = envp;
	inf.lenv = make_env_list(envp);
	signal(SIGQUIT, sig_quit);
	signal(SIGINT, sig_hand);

	inf.line = ft_strdup("");
    if (!inf.line || ft_strlen(inf.line) == 0)
        exit(0);
	// ft_putendl_fd(inf.line, 2);
	if (inf.line == NULL)
		exit_ms("exit", 0);
	inf.line = expand_dol(inf.line);
	// ft_putendl_fd(inf.line, 2);
	inf.pipes = parse(inf.line);
	free(inf.line);
	inf.line = NULL;
	// print_pipes(inf.pipes);
	if (PIPES)
		exec();
	inf.pipes = free_pipes(inf.pipes);
	inf.mask = 0;
	return (inf.code);
}
#endif

