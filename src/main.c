#include "../includes/minishell.h"

void	goodbye(int signum)
{
	printf("%d\n", signum);
	printf("goodbye, my friend\n");
}

void	ft_str(t_mshell *shell, char *str, int j)
{
	int	i;

	i = -1;
	while (str[++ i])
	{
		shell->t_env[j][i] = str[i];
	}
	shell->t_env[j][i] = '\0';
}

void	ft_parse(char	**envp, t_mshell *shell)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
		i ++;
	shell->t_env = malloc(i);
	i = -1;
	while (envp[++ i])
	{
		j = 0;
		while (envp[i][j])
			j ++;
		shell->t_env[i] = malloc(sizeof(char) * j + 1);
		ft_str(shell, envp[i], i);
	}
}

int	main(int argc, char *argv[], char **envp)
{
	// t_mshell	shell;
	int	i;

	i = 0;
	(void)argv;
	envp[i] = "!sosi!";
	// ft_parse(envp, &shell);
	// while(shell.t_env[++ i])
	// {
	// 	printf("%s\n", shell.t_env[i]);
	// }
	i = -1;
	while(envp[++ i])
	{
		printf("%s\n", envp[i]);
	}
	if (argc == 0)
		write(2, "Error\n", 6);
	signal(SIGINT, goodbye);
	while(1)
	{
		printf("your answer: %s\n", readline(PROMPT));
	}
}
