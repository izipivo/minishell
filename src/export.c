#include "../includes/minishell.h"

int ft_strlen_env(char *en); //del; -->minishell.h
t_env	*add_variable(t_env	*lenv, int ac, char **av); //del; -->minishell.h
char *parse_inf_key(char *s); //del; -->minishell.h
char *parse_inf_val(char *s); //del -->minishell.h
void	print_exp(char **exp); // //del -->minishell.h
void free_exp(char **exp); // //del -->minishell.h

char **join_env(t_mshell	*inf, char **result, int i)
{
	char *tmp_del;

	while (i != (unsigned long) -1)
	{
		result[i] = ft_strdup(inf->lenv->key);
		tmp_del = result[i];
		result[i] = ft_strjoin(result[i], "=");
		free(tmp_del);
		tmp_del = result[i];
		result[i] = ft_strjoin(result[i], "\"");
		free(tmp_del);
		tmp_del = result[i];
		result[i] = ft_strjoin(result[i], inf->lenv->val);
		free(tmp_del);
		tmp_del = result[i];
		result[i] = ft_strjoin(result[i], "\"");
		free(tmp_del);
		i --;
		inf->lenv = inf->lenv->next;
	}
	return (result);
}

char	**ft_exp(t_mshell	*inf)
{
	int i;
	char **result;
	void *tmp;
	char *tmp_del;

	i = 0;
	tmp = inf->lenv;
	while (inf->lenv)
	{
		i ++;
		inf->lenv = inf->lenv->next;
	}
	inf->lenv = tmp;
	result = (char **)malloc(sizeof(char *) * (i + 1));
	if (!result)
		return (NULL);
	result[i] = 0;
	i --;
	result = join_env(inf, result, i);
	inf->lenv = tmp;
	return (result);
}

void	sort_env(t_mshell	*inf)
{
	char	**exp;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	exp = ft_exp(inf);
	while (exp[i])
	{
		j = i + 1;
		while (exp[j])
		{
			if (ft_strncmp(exp[i], exp[j], ft_strlen_env(exp[j])) > 0)
			{
				tmp = exp[i];
				exp[i] = exp[j];
				exp[j] = tmp;
			}
			j ++;
		}
		i ++;
	}
	print_exp(exp);
	free_exp(exp);
    //ликов нет!
}

extern t_mshell inf;

void export_main(void)
{
	char **exp;
	// t_mshell	inf;
	int i;
	

	i = 0;
	while (inf.pipes[0].cmd[i])
		i ++;
	// inf.lenv = make_env_list(envp);
	// if (argc > 2)
	inf.lenv = add_variable(inf.lenv, i, inf.pipes->cmd);
	sort_env(&inf);
	// free_lenv(inf.lenv);
	return ;
}


//gcc export.c ../../includes/minishell.h ../../libft/ft_strjoin.c ../../libft/ft_strlen.c ../../libft/ft_strchr.c ../../libft/ft_strdup.c ../env_list.c export_utils.c ../../libft/ft_strncmp.c update.c 