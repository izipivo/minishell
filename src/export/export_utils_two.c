#include "minishell.h"

extern t_mshell	inf;

char	**tmp_cmd(char **cmd, char **tmp)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		cmd[i] = parse_inf_key(tmp[i]);
		i ++;
	}
	return (cmd);
}

void	error_print(char *str, int i)
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

char	*ft_strjoin_exp(char *result, char *tmp_del, t_mshell *inf)
{
	result = ft_strjoin(result, "=");
	free(tmp_del);
	tmp_del = result;
	result = ft_strjoin(result, "\"");
	free(tmp_del);
	tmp_del = result;
	result = ft_strjoin(result, inf->lenv->val);
	free(tmp_del);
	tmp_del = result;
	result = ft_strjoin(result, "\"");
	free(tmp_del);
	return (result);
}

char	**back_cmd(char **cmd, char **tmp)
{
	int	i;

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
	free(tmp);
	return (cmd);
}

void	dubl_exp(int index)
{
	char	**tmp;

	if (same_key() == -1)
	{
		tmp = new_key(inf.pipes[index].cmd);
		inf.pipes[index].cmd = tmp_cmd(inf.pipes[index].cmd, tmp);
		unset_main(index);
		inf.pipes[index].cmd = back_cmd(inf.pipes[index].cmd, tmp);
	}
}
