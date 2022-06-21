#include "minishell.h"

extern t_mshell inf;

char **join_env(t_mshell	*inf, char **result, int i)
{
	char *tmp_del;

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
	// char *tmp_del;

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
}

void error_print(char *str, int i)
{
	if (str[i] == 33)
	{
		while (str[i])
		{
			write(2, &str[i], 1);
			i ++;
		}
		printf(": %s\n", "event not found");
	}
	else
		printf("«%s»: %s\n",str , "это недопустимый идентификатор");
}

int	check_pipes_cmd(char *str)
{
	int i;

	i = 0;
	if (str[i] >= '0' && str[i] <= '9')
		return (1);
	while (str[i])
	{
		if ((check_key(str[i])) == 1)
		{
			error_print(str, i);  //потом изменить!
			return (1);
		}
		i ++;
	}
	return (-1);
}

char **back_cmd(char **cmd, char **tmp)
{
	int i;

	i = 0;
	while (tmp[i])
	{
		free(cmd[i]);
		cmd[i] = ft_strdup(tmp[i]);
		i ++;
	}
	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i ++;
	}
		free(tmp[i]);
	free(tmp);
	return (cmd);
}

char **tmp_cmd(char **cmd, char **tmp)
{
	int i;

	i = 0;
	while(cmd[i])
	{
		free(cmd[i]);
		cmd[i] = parse_inf_key(tmp[i]);
		i ++;
	}
	return (cmd);
}

void export_main(void)
{
	char **tmp;
	int i;
	
	i = 0;
	if (same_key() == -1)
	{
		tmp = new_key(inf.pipes[0].cmd);
		inf.pipes[0].cmd = tmp_cmd(inf.pipes[0].cmd, tmp);
		unset_main();
		inf.pipes[0].cmd = back_cmd(inf.pipes[0].cmd, tmp);
	}
	while (inf.pipes[0].cmd[i])
	{
		if (check_pipes_cmd(inf.pipes[0].cmd[i]) == 1)
			return ;
		i ++;
	}
	if (i > 1)
	{
		inf.lenv = add_variable(inf.lenv, i, inf.pipes->cmd);
		return ;
	}
	sort_env(&inf);
	return ;
}