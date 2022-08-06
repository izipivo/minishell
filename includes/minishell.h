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
/* # define PROMPT RED "MI"ORANGE"NI"LYELLOW"GA"GREEN"YS"BRIGHT_BLUE"HE"SINIY"LL"\
	//PURPLE "$> "RESET*/
# define PERROR YELLOW "mini" RED "error" RESET
# define PROMPT "pcheloshell?> "
// # define RL_PROMT_START_IGNORE '\001'
// # define RL_PROMT_END_IGNORE '\002'

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

# define PIPES (g_inf.mask >> 16)
# define OUT(x) ((x >> 1) & 1)
# define APP(x) (((x >> 1) & 1) ? (0) : (1))
# define HD(x) ((x & 1) ? (0) : (1))
# define INPUT(x) (x & 1)
# define DLR(x) (x & 1)
# define QUOTS(x) ((x >> 1) & 1)
# define DIGIT(x) ((x >> 2) & 1)
# define UPDATELENV(x) ((x >> 4) & 1)
# define PIPE_OK 1
# define PIPE_KO 0
# define EXIT_ERROR 1

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
	//	1 значит один знак "<"/">", 0 - два знака "<"/">"
	char 			mask;
	struct s_pipes	*next;
}					t_pipes;

typedef	struct		s_mshell
{
	char			*line;
	char			**env;
	char 			**env_cpy;
	//	первые 16 бит кол-во пайпов, последний бит 1 если надо поменять доллар; 2ой 1:есть доллар 0:нет доллара;
	//	3ий с конца бит 1: если в токене доллара первый символ цифра; 0: не единица; 4 bit update_lenv
	int				mask;
	int				code;
	t_env			*lenv;
	t_list			*tokens;
	t_pipes			*pipes;
	pid_t			*pids;
}					t_mshell;

void	*free_pipes(t_pipes *pipes);
void	*free_lenv(t_env *lenv);
t_env	*make_env_list(char **envp);
t_pipes	*parse(char *line);
void	print_list(t_list *tok);
void	free_val(t_list *token);
void	*free_tokens(t_list *tokens);
int		count_pipes(t_list *token);
int		token_key(char line);
void	sig_hand(int sig);
void	sig_quit(int sig);
void	exec(void);
void	print_pipes(t_pipes *pipe);
int		unset_main(int index);
void    unset_env_list(t_env *lenv, char **del);
int		env_main(int index);
char    *expand_dol(char *line);
char	*find_env(char *find);
int		cd_main(char **cmd, int index);
void	exit_ms(char *err, int status);
int 	ft_strlen_env(char *en);
void	add_variable(t_env	*lenv, char **av);
char	*parse_inf_key(char *s);
char	*parse_inf_val(char *s);
void	print_exp(char **exp);
void 	free_exp(char **exp);
int		check_key(char c);
int 	same_key(void);
char	**new_key(char **cmd);
void	strapp(char **s1, char *s2, int f);
void	print_string(char **str);
void	exit_main(int index);
int 	echo_main(int argc, char **argv);
int		pwd_main(void);
void    check_pipes(t_list *token);
t_pipes	*copy_pipes(t_pipes *new, t_list *old);
void	cap(t_pipes *new, int i, int j);
void	copy_out(t_pipes *new, char *val, char key);
int		q_args(t_list *token);
void	remove_quotes(t_list *token);
int		join_commands(t_list *token);
t_pipes	*remalloc(void);
void	strapp(char **s1, char *s2, int f);
void	strapp2(char *str, char **s2);
t_pipes	*cleaning(void);
int		same_token(char old, char new);
void	check_pipes(t_list *token);
int	fill_token(int old, char new, int *token_index, int *val_index);
void	make_new_token(int *token_index, int *val_index, char key);
int		tok_quant(char *line);
char	*joinlist(t_list **bl);
char	*replace_dollar(char *line, int start, int end);
int		isdollar(char *line, int i);
t_list	*newlst(char *val, int start, int end, char *str);
char	**cmdparse(char **new, char **envp, int **fd);
void	killchild(char **cmd, int **fd);
int		close_all(int **fd);
int		str_len(char **str);
void	child_fd(int index, int **fd);
int	check_func(t_pipes *pipes, int parent, int index);
#endif
