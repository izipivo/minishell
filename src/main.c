#include "minishell.h"

/*
//		main 
*/

extern t_mshell	inf;

char	**copy_env(char **env)
{
	int i;
	int j;
	char **copy;

	i = 0;
	j = 0;
	while (env[i])
		i ++;
	copy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!copy)
		exit_ms("malloc", 0);
	copy[i] = 0;
	j = i;
	while (i > 0)
	{
		copy[i - 1] = ft_strdup(env[j - 1]);
		i --;
		j --;
	}
	return (copy);
}

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
// 	while (3)
// 	{
// 	// if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
//  	// {
// 		line = readline(PROMPT);
// 		// line = argv[2];
// 		if (!ft_strlen(line))
// 		{
// 			free(line);
// 			continue ;
// 			// exit(0);
// 		}
// 		inf.pipes = parse(line);
// 		add_history(line);
// 		free(line);
// 		// print_pipes(inf.pipes);
// 		if (PIPES)
// 		{
// 			// ft_putnbr_fd(PIPES, 1);
// 			exec();
// 		}
// 		inf.pipes = free_pipes(inf.pipes);
// 		inf.mask = 0;
// 	}
// }


int     main(int argc, char **argv, char **envp)
{
	char		*line;
	// t_list		*tokens;
	(void)argc;
	(void)argv;
	ft_memset(&inf, 0, sizeof(t_mshell));
	inf.env = envp;
	inf.env_cpy = copy_env(envp);
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
		inf.pipes = parse(line);
		add_history(line);
		free(line);
		// print_pipes(inf.pipes);
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
//  	(void)argc;
//  	(void)argv;
//  	ft_memset(&inf, 0, sizeof(t_mshell));
//  	inf.env = envp;
// 	inf.env_cpy = copy_env(envp);
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
//  		inf.pipes = parse(line);
//  		if (PIPES)
//  		{
//  			// ft_putnbr_fd(PIPES, 1);
//  			exec();
//  		}
//  		inf.pipes = free_pipes(inf.pipes);
//  		inf.mask = 0;
//  	}
//  }


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
// 	line = "echo $USER $USER9999 $USER8888 $USER7777";
// 	inf.pipes = parse(line);
// 	if (PIPES)
// 	{
// 		// ft_putnbr_fd(PIPES, 1);
// 		exec();
// 	}
// 	inf.pipes = free_pipes(inf.pipes);
// 	inf.mask = 0;
// }
