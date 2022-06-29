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

void error_print(char *str, int i)
{
	if (str[i] == 33)
	{
		ft_putstr_fd("minishell: ", 2);
		while (str[i])
		{
			write(2, &str[i], 1);
			i ++;
		}
		ft_putstr_fd(": event not found\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
}

char *new_pipes_cmd(char *cmd)
{
	int i;
	int j;
	char *res;

	i = 0;
	j = 0;
	while (cmd[i])
		i ++;
	res = (char *)malloc(sizeof(char) * i);
	if (!res)
		exit_ms("error malloc", -1);
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == 43 && cmd[i + 1] == 61)
		{
			i ++;
			continue;
		}
		res[j] = cmd[i];
		// printf("%c", res[i]);
		i ++;
		j ++;
	}
	res[j] = 0;
	free(cmd);
	return(res);

}

int	check_pipes_cmd(char *str)
{
	int i;
	// char *tmp;

	i = 0;
	if (str[i] >= '0' && str[i] <= '9')
		return (1);
	while (str[i] && str[i] != 61)
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

int export_main(int index)
{
	char **tmp;
	int i;
	int flag;

	flag = 0;
	i = 0;
	if (same_key() == -1)
	{
		tmp = new_key(inf.pipes[index].cmd);
		inf.pipes[index].cmd = tmp_cmd(inf.pipes[index].cmd, tmp);
		unset_main(index);
		inf.pipes[index].cmd = back_cmd(inf.pipes[index].cmd, tmp);
	}
	while (inf.pipes[index].cmd[i])
	{
		flag = check_pipes_cmd(inf.pipes[index].cmd[i]);
		if (flag == 1)
			return (0);
		else if (flag == 2)
		{
			i = 0;
			continue;
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