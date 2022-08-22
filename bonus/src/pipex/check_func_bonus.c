/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:59:08 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/11 15:20:12 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

extern t_mshell	g_inf;

static int	conti2(t_pipes *pipes, int parent)
{
	if (!(ft_strncmp(pipes->cmd[0], "echo", 5)))
	{
		if (!parent)
		{
			g_inf.code = echo_main(str_len(pipes->cmd), pipes->cmd);
			return (1);
		}
		else
			return (1);
	}
	else if (!(ft_strncmp(pipes->cmd[0], "pwd", 4)))
	{
		if (!parent)
		{
			g_inf.code = pwd_main();
			return (1);
		}
		else
			return (0);
	}
	return (256);
}

static int	conti(t_pipes *pipes, int parent, int index)
{
	if (!(ft_strncmp(pipes->cmd[0], "unset", 7)))
	{
		if (parent)
		{
			g_inf.code = unset_main(index);
			return (1);
		}
		else
			return (1);
	}
	else if (!(ft_strncmp(pipes->cmd[0], "exit", 5)))
	{
		if (parent)
			exit_main(index);
		else
			return (1);
	}
	else if (!(ft_strncmp(pipes->cmd[0], "cd", 5)))
	{
		if (parent)
			g_inf.code = cd_main(pipes->cmd, index);
		else
			return (1);
	}
	return (conti2(pipes, parent));
}

int	check_func(t_pipes *pipes, int parent, int index)
{
	if (!pipes->cmd || !pipes->cmd[0])
		return (12);
	if (!(ft_strncmp(pipes->cmd[0], "export", 8)))
	{
		if (parent && pipes->cmd[1])
		{
			g_inf.code = export_main(index);
			return (1);
		}
		else if (!parent && !pipes->cmd[1])
		{
			g_inf.code = export_main(index);
			return (1);
		}
		else
			return (1);
	}
	else if (!(ft_strncmp(pipes->cmd[0], "env", 4)))
	{
		if (!parent)
			return (env_main(index));
		else
			return (1);
	}
	return (conti(pipes, parent, index));
}

char	**cmdparse(char **new, char **envp, int **fd)
{
	char	*tmp;

	tmp = new[0];
	new[0] = checkpath(tmp, envp, fd);
	return (new);
}

void	killchild(char **cmd, int **fd)
{
	(void)cmd;
	(void)fd;
	free_pipes(g_inf.pipes);
	close(0);
	close(1);
	exit(EXIT_SUCCESS);
}
