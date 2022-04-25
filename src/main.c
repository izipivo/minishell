#include "../includes/minishell.h"

void	goodbye(int signum)
{
	printf("%d\n", signum);
	printf("goodbye, my friend\n");
}

int	main(void)
{
	signal(SIGINT, goodbye);
	while(1)
	{
		printf("your answer: %s\n", readline(PROMPT));
	}
}
