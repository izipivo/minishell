#ifndef	MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <dirent.h>

#define CYELLOW "\001\e[0;31m\002"
#define YELLOW "\001\033[1;93m\002"
# define READLINE_BLUE		"\001\033[1;94m\002"
#define RESET   "\001\e[0m\002"
# define RED "\001\033[1;91m\002"
# define PROMPT YELLOW "MINI" READLINE_BLUE "GAY" YELLOW "SHELL$> " RESET
#define PERROR YELLOW "mini" RED "error" RESET

typedef	struct	p_mshell
{
	char	**t_env;
	
}				t_mshell;

#endif
