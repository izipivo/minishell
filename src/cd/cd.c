/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdpwdechoexit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:37:50 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/11 12:43:17 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_mshell	g_inf;

void	free_strs(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
}

char	**cp_cmd(void)
{
	char	**buf;

	buf = (char **)malloc(sizeof(char *) * (3));
	if (!buf)
		exit_ms("malloc rip", 1);
	buf[0] = ft_strdup("export");
	if (!buf[0])
		exit_ms("malloc rip", 1);
	buf[1] = ft_strdup("PWD=");
	if (!buf[1])
		exit_ms("malloc rip", 1);
	strapp(&buf[1], getcwd(NULL, 0), 2);
	if (!buf[1])
		exit_ms("malloc rip", 1);
	buf[2] = NULL;
	return (buf);
}

char	**cp_oldpwd(void)
{
	char	**buf;

	buf = (char **)malloc(sizeof(char *) * (3));
	if (!buf)
		exit_ms("malloc rip", 1);
	buf[0] = ft_strdup("export");
	if (!buf[0])
		exit_ms("malloc rip", 1);
	buf[1] = ft_strdup("OLDPWD=");
	if (!buf[1])
		exit_ms("malloc rip", 1);
	strapp(&buf[1], getcwd(NULL, 0), 2);
	if (!buf[1])
		exit_ms("malloc rip", 1);
	buf[2] = NULL;
	return (buf);
}

int	cd(char	*path, int index)
{
	char	**cp;
	int		error;

	cp = g_inf.pipes[index].cmd;
	g_inf.pipes[index].cmd = cp_oldpwd();
	error = chdir(path);
	if (!error)
	{
		export_main(index);
		free_strs(g_inf.pipes[index].cmd);
		g_inf.pipes[index].cmd = cp_cmd();
		export_main(index);
		free_strs(g_inf.pipes[index].cmd);
	}
	else
	{
		free_strs(g_inf.pipes[index].cmd);
		perror(PERROR);
	}
	g_inf.pipes[index].cmd = (char **)cp;
	if (error)
		return (1);
	return (0);
}

int	cd_main(char **cmd, int index)
{
	if (cmd && cmd[0] && cmd[1])
	{
		if (access(cmd[1], F_OK) != 0)
		{
			perror(cmd[1]);
			return (1);
		}
		return (cd(cmd[1], index));
	}
	return (0);
}
