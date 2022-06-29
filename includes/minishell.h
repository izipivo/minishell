#ifndef	MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
#include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <dirent.h>
# include "pipex.h"

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
# define PERROR YELLOW "mini" RED "error" RESET
# define PROMPT "gay?> "

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

# define PIPES (inf.mask >> 16)
# define OUT(x) ((x >> 1) & 1)
# define APP(x) (((x >> 1) & 1) ? (0) : (1))
# define HD(x) ((x & 1) ? (0) : (1))
# define INPUT(x) (x & 1)
# define DLR(x) (x & 1)
# define QUOTS(x) ((x >> 1) & 1)
# define DIGIT(x) ((x >> 2) & 1)
# define UPDATELENV(x) ((x >> 4) & 1)

typedef struct	s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}					t_env;

typedef struct		s_pipes
{
	char			**cmd;
	char			*in;
	char			*out;
	char 			mask;					//1 значит один знак "<"/">", 0 - два знака "<"/">"
	struct s_pipes	*next;
}					t_pipes;

typedef	struct		s_mshell
{
	char			**env;
	char 			**env_cpy;
	int				mask;					//	первые 16 бит кол-во пайпов, последний бит 1 если надо поменять доллар; 2ой 1:есть доллар 0:нет доллара; 3ий с конца бит 1: если в токене доллара первый символ цифра; 0: не единица; 4 bit update_lenv
	t_env			*lenv;
	t_list			*tokens;
	t_pipes			*pipes;
	pid_t			*pids;
}					t_mshell;

void	*free_pipes(t_pipes *pipes);
void	*free_lenv(t_env *lenv);
t_env	*make_env_list(char **envp);
int		ft_arrlen(char **arr);
void	free_list(t_list *list);
t_pipes	*parse(char *line);
void	print_list(t_list *tok);
void	free_val(t_list *token);
void	*free_tokens(t_list *tokens);
void	*free_pipex_args(char **ar, int pipes);
int		count_pipes(t_list *token);
int		ft_strapp(char **s1, char *s2);
void	dol_spc_str(void);
int		dollar(t_list *dlr);
int		dollar_find(t_list *token);
void	streams(t_list *token);
int		is_separator(char c);
int		make_token(t_list *token, char *line, int end, int shift, int sep);
int		token_key(char line);
t_pipes	*invalid_args(void);
void	sig_hand(int sig);
void	sig_quit(int sig);
void	exec(void);
void	print_pipes(t_pipes *pipe);
int		unset_main(int index);
t_env	*delete_env_unset(t_env *lenv, t_env *lenv_tmp, int num, char **del);
int		i_num(t_env	*lenv_tmp);
int	 	env_main(void);
void	exit_ms(char *err, int status);
int 	ft_strlen_env(char *en);
t_env	*add_variable(t_env	*lenv, int ac, char **av);
char	 *parse_inf_key(char *s);
char 	*parse_inf_val(char *s);
void	print_exp(char **exp);
void 	free_exp(char **exp);
int		check_key(char c);
int 	same_key(void);
char	**new_key(char **cmd);
char	*ft_strjoin_exp(char *result, char *tmp_del, t_mshell *inf);
char	*new_pipes_cmd(char *cmd);
void	error_print(char *str, int i);
void	dubl_exp(int index);
void	strapp(char **s1, char *s2, int f);
void	print_string(char **str);
void	exit_main(int index);

#endif
