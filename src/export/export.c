#include "minishell.h"

extern t_mshell	inf;

char	**join_env(t_mshell	*inf, char **result, int i)
{
	char	*tmp_del;

	while ((unsigned long) i != (unsigned long) -1)
	{
		result[i] = ft_strdup(inf->lenv->key);
		tmp_del = result[i];
		if (inf->lenv->val[0] == '\0')
		{
			i --;
			inf->lenv = inf->lenv->next;
			continue ;
		}
		if (inf->lenv->val[0] == '=' && inf->lenv->val[1] == '\0')
		{
			result[i] = ft_strjoin(result[i], "=");
			free(tmp_del);
			i --;
			inf->lenv = inf->lenv->next;
			continue ;
		}
		result[i] = ft_strjoin_exp(result[i], tmp_del, inf);
		i --;
		inf->lenv = inf->lenv->next;
	}
	return (result);
}

char	**ft_exp(t_mshell	*inf)
{
	int		i;
	char	**result;
	void	*tmp;

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
		exit_ms("error malloc", -1);
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
}

int	check_pipes_cmd(char *str)
{
	int	i;

	i = 0;
	if (str[i] >= '0' && str[i] <= '9')
		return (1);
	while (str[i] && str[i] != 61)
	{
		if ((check_key(str[i])) == 1)
		{
			error_print(str, i);
			return (1);
		}
		i ++;
	}
	return (-1);
}

int	export_main(int index)
{
	int		i;
	int		flag;

	flag = 0;
	i = 0;
	dubl_exp(index);
	while (inf.pipes[index].cmd[i])
	{
		flag = check_pipes_cmd(inf.pipes[index].cmd[i]);
		if (flag == 1)
			return (0);
		else if (flag == 2)
		{
			i = 0;
			continue ;
		}
		i ++;
	}
	if (i > 1)
	{
		inf.lenv = add_variable(inf.lenv, i, inf.pipes[index].cmd);
		return (0);
	}
	sort_env(&inf);
	return (0);
}
