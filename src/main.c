#include "minishell.h"

/*
//		main 
*/

extern t_mshell	inf;

// int     main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
// 	ft_memset(&inf, 0, sizeof(t_mshell));
// 	inf.env = envp;
// 	inf.lenv = make_env_list(envp);
// 	signal(SIGQUIT, sig_quit);
// 	signal(SIGINT, sig_hand);
// 	while (3)
// 	{
// 		inf.line = readline(PROMPT);
// 		if (inf.line == NULL)
// 			exit_ms("exit", 0);
// 		if (!ft_strlen(inf.line))
// 		{
// 			free(inf.line);
// 			continue ;
// 		}
// 		add_history(inf.line);
// 		inf.line = expand_dol(inf.line);
// 		// printf("%s\n", line);
// 		inf.pipes = parse(inf.line);
// 		free(inf.line);
// 		inf.line = NULL;
// 		// print_pipes(inf.pipes);
// 		if (PIPES)
// 			exec();
// 		inf.pipes = free_pipes(inf.pipes);
// 		inf.mask = 0;
// 	}
// }



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
	
	inf.line = ft_strdup(argv[2]);
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
}

/*
//		main для gdb
*/

// int     main(int argc, char **argv, char **envp)
// {
// 	char		*line;
// 	// t_list		*tokens;
// 	(void)argc;
// 	(void)argv;
// 	ft_memset(&inf, 0, sizeof(t_mshell));
// 	inf.env = envp;
// 	inf.lenv = make_env_list(envp);
// 	signal(SIGQUIT, sig_quit);
// 	signal(SIGINT, sig_hand);
// 	line = "cat Makefile | grep all";
// 	inf.pipes = parse(line);
// 	if (PIPES)
// 	{
// 		// ft_putnbr_fd(PIPES, 1);
// 		exec();
// 	}
// 	inf.pipes = free_pipes(inf.pipes);
// 	inf.mask = 0;
// }
