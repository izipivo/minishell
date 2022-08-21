/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:59:08 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/11 15:20:12 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <dirent.h>
# include <dirent.h>

# include "pipex.h"
# include "../libft/libft.h"
# include "minishell_defines.h"

typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}					t_env;

//	1 значит один знак "<"/">", 0 - два знака "<"/">"
typedef struct s_pipes
{
	char			**cmd;
	char			*in;
	char			*out;
	char			mask;
	struct s_pipes	*next;
}					t_pipes;

//	первые 16 бит кол-во пайпов, последний бит 1 если надо поменять доллар;
//	2ой 1:есть доллар 0:нет доллара;
//	3ий с конца бит 1: если в токене доллара первый символ цифра;
//	0: не единица;
//	4 bit update_lenv 1:надо обновить 2:не надо
typedef struct s_mshell
{
	char			*line;
	char			**env;
	char			**env_cpy;
	int				mask;
	int				code;
	int				line_len;
	t_env			*lenv;
	t_list			*tokens;
	t_pipes			*pipes;
	pid_t			*pids;
}					t_mshell;

typedef struct s_wldcrd
{
	char			*file;
	struct s_wldcrd	*next;
}					t_wldcrd;

void	*free_pipes(t_pipes *pipes);
void	*free_lenv(t_env *lenv);
t_env	*make_env_list(char **envp);
t_pipes	*parse(char *line, int i, int n);
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
void	unset_env_list(t_env *lenv, char **del);
int		env_main(int index);
char	*expand_dol(char *line);
char	*find_env(char *find);
int		cd_main(char **cmd, int index);
void	exit_ms(char *err, int status);
int		ft_strlen_env(char *en);
void	add_variable(t_env	*lenv, char **av);
char	*parse_inf_key(char *s);
char	*parse_inf_val(char *s);
void	print_exp(char **exp);
void	free_exp(char **exp);
int		check_key(char c);
int		same_key(void);
char	**new_key(char **cmd);
void	strapp(char **s1, char *s2, int f);
void	print_string(char **str);
void	exit_main(int index);
int		echo_main(int argc, char **argv);
int		pwd_main(void);
int		check_pipes(t_list *token);
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
int		check_pipes(t_list *token);
int		fill_token(int old, char new, int *token_index, int *val_index);
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
int		check_func(t_pipes *pipes, int parent, int index);
char	*wldcrd(char *str);
void	free_list(t_wldcrd *list);
char	*select_and_join(t_wldcrd *list, char *str);
void	check_wildcards(t_list *tokens);
char	*find_wildcard_word(char **splt);
void	ft_check(int index);
int		ft_run(int i, int index);
char	**ft_exp(t_mshell	*g_inf);
char	*one_c(char *c, int flag);
void	sort_env(t_mshell	*g_inf);
char	**back_cmd(char **cmd, char **tmp);
void	del_unset(t_env *prev);
int		check_redirs(t_list *token);
void	ft_check(int index);
int		return_prompt(char *err, int status);
int		list_len(t_env *lenv);
void	*free_env(char **env);

#endif
