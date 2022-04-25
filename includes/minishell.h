#ifndef	MINISHELL_H
# define MINISHELL_H
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
# define PROMPT "\001\033[1;93m\002" "MINI\001\033[1;94m\002" "GAY\001\033[1;93m\002SHELL$> \001\e[0m\002"


#endif
