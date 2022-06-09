#include "../../includes/minishell.h"

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

int main(int argc, char *argv[], char *envp[])
{
	char **exp;
	(void)argc;
	(void)argv;
	t_mshell	inf;

	inf.lenv = make_env_list(envp);
	if (argc > 2)
		add_variable(&inf, argc, argv);
	sort_env(&inf);
	free_lenv(inf.lenv);
	return (0);
}

//gcc export.c ../../includes/minishell.h ../../libft/ft_strjoin.c ../../libft/ft_strlen.c ../../libft/ft_strchr.c ../../libft/ft_strdup.c ../env_list.c export_utils.c ../../libft/ft_strncmp.c