#ifndef	MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <dirent.h>
/*
//		readline colours
*/
# define CYELLOW "\001\e[0;31m\002"
# define YELLOW "\001\033[1;93m\002"
# define READLINE_BLUE		"\001\033[1;94m\002"
# define RESET   "\001\e[0m\002"
# define RED "\001\033[1;91m\002"
# define PROMPT YELLOW "MINI" READLINE_BLUE "GAY" YELLOW "SHELL$> " RESET
# define PERROR YELLOW "mini" RED "error" RESET
/*
//		token's keys
*/
# define COMMAND 0
# define PIPE 1
# define INFILE 2
# define OUTFILE 3
# define DQUOTES 4
# define SQUOTES 5
# define APPEND 6 		//	>>
# define HEREDOC 7
# define SPACE 8
# define AND 9
# define OR 10
# define PARENT_O 11
# define PARENT_C 12
# define DOLLAR 13

typedef struct	s_token
{
	char		key;
	char		**val;
	char		in_q;		// 0 - не в кавычках; 1 - в одинарных; 2 - в двойных
}				t_token;

typedef	struct	p_mshell
{
	char		**env;
	t_token		*tokens;
}				t_mshell;

#endif
