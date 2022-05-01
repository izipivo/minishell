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
# define YELLOW "\001\033[1;33m\002"
# define LYELLOW "\e[38;5;227m"
# define READLINE_BLUE "\001\033[1;94m\002"
# define RESET   "\001\e[0m\002"
# define RED "\001\033[1;91m\002"
# define GREEN "\e[00;32m"
# define SINIY "\e[00;34m"
# define PURPLE "\e[00;35m"
# define BRIGHT_BLUE "\e[01;34m"
# define ORANGE "\e[38;5;202m"
# define PROMPT RED "MI"ORANGE"NI"LYELLOW"GA"GREEN"YS"BRIGHT_BLUE"HE"SINIY"LL"\
	PURPLE "$> "RESET
# define PERROR YELLOW "mini" RED "error" RESET
/*
//		token's keys
*/
# define AND 0 			//	&&
# define PIPE 1			//	|
# define OR 2			//	||
# define INFILE 3		//	<
# define HEREDOC 4		//	<<
# define OUTFILE 5		//	>
# define APPEND 6 		//	>>
# define DQUOTES 7		//	"
# define SQUOTES 8		//	'
# define SPC 9			//	_
# define COMMAND 10		//	...
# define PARENT_O 11	//	(
# define PARENT_C 12	//	)
# define DOLLAR 13		//	$

typedef struct	s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}				t_env;


typedef	struct	s_mshell
{
	char		**env;
	t_env		*lenv;
	t_list		*tokens;
}				t_mshell;

void	free_lenv(t_env *lenv);
t_env	*make_env_list(char **envp);
int	ft_arrlen(char **arr);

#endif
