#include "minishell.h"

/*
//		main 
*/

extern t_mshell	inf;

int     main(int argc, char **argv, char **envp)
{
	char		*line;
	t_list		*tokens;
	(void)argc;
	(void)argv;
	ft_memset(&inf, 0, sizeof(t_mshell));
	inf.env = envp;
	inf.lenv = make_env_list(envp);
	signal(SIGQUIT, sig_quit);
	signal(SIGINT, sig_hand);
	while (3)
	{
	// if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
 	// {
		line = readline(PROMPT);
		// line = argv[2];
		if (!ft_strlen(line))
		{
			free(line);
			continue ;
			// exit(0);
		}
		add_history(line);
		inf.pipes = parse(line, inf.lenv);
		free(line);
		print_pipes(inf.pipes);
		if (PIPES)
		{
			// ft_putnbr_fd(PIPES, 1);
			exec();
		}
		inf.pipes = free_pipes(inf.pipes);
		inf.mask = 0;
	}
}

/*
//		main для тестера
*/

//  int     main(int argc, char **argv, char **envp)
//  {
//  	char		*line;
//  	t_list		*tokens;
//  	(void)argc;
//  	(void)argv;
//  	ft_memset(&inf, 0, sizeof(t_mshell));
//  	inf.env = envp;
//  	inf.lenv = make_env_list(envp);
//  	signal(SIGQUIT, sig_quit);
//  	signal(SIGINT, sig_hand);
//  	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
//    	{
//  		line = argv[2];
//  		if (!ft_strlen(line))
//  		{
//  			exit(0);
//  		}
//  		inf.pipes = parse(line, inf.lenv);
//  		if (PIPES)
//  		{
//  			// ft_putnbr_fd(PIPES, 1);
//  			exec();
//  		}
//  		inf.pipes = free_pipes(inf.pipes);
//  		inf.mask = 0;
//  	}
//  }
