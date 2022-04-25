#include "../includes/minishell.h"
void	prit(char **envp)
{

	int i=-1;
	while (envp[++i])
	{
		if (strstr(envp[i],"PWD"))
			printf("%s\n", envp[i]);
	}
}
int	main(int args, char **argv, char **envp)
{
	prit(envp);
	chdir("~/");
	prit(envp);
	printf("%s\n", getenv("PWD"));
	envp[0] = "jj";
	printf("%s\n", envp[0]);
}
