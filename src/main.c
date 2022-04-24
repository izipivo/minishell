#include "../includes/minishell.h"
#define CYELLOW "\001\e[0;31m\002"
#define YELLOW "\001\033[1;93m\002"
# define READLINE_BLUE		"\001\033[1;94m\002"
#define RESET   "\001\e[0m\002"
int	main(void)
{
	while(1)
	{
		printf("your answer: %s\n", readline(YELLOW "why are you "
					READLINE_BLUE "gay" YELLOW "? " RESET));
	}
}
