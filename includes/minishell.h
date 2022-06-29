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
# define PROMPT "CHECHNYA_KRUTO!> "
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
	char			*pwd;
	int				mask;					//	первые 16 бит кол-во пайпов, последний бит 1 если надо поменять доллар; 2ой 1:есть доллар 0:нет доллара; 3ий с конца бит 1: если в токене доллара первый символ цифра; 0: не единица; 4 bit update_lenv
	int				status;
	t_env			*lenv;
	t_list			*tokens;
	t_pipes			*pipes;
	pid_t			pid;
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
int		cd_main(char **cmd, int index);
int		echo_main(int argc, char **argv);
int		pwd_main(void);
// parsers
int		same_token(char old, char new);
t_pipes	*cleaning(void);
int		get_last_char_of_dlr(char *str, t_list *token);
char	*find_env(char *find);
t_pipes	*remalloc(void);
t_pipes	*copy_pipes(t_pipes *new, t_list *old);
void	cap(t_pipes *new, int i, int j);
void	copy_out(t_pipes *new, char *val, char key);
void	copy_in(t_pipes *new, char *val, char key);
int		copy_word(t_pipes *new, int j, t_list *old);
t_pipes	*del(t_pipes *new);
int		join_commands(t_list *token, int f);
int		list_size(t_list *list);
int		token_cp(t_list *new, t_list *old);
int		q_args(t_list *token);
t_pipes	*stop_exec(t_pipes *new);
t_pipes	*end_pipes(t_pipes *new, int i, int j);
void	check_dlr(t_list *token);
int		tok_quant(char *line);
void	make_new_token(int *token_index, int *val_index, char key);
#endif
