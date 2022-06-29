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

extern t_mshell	inf;

char	**cp_cmd(void)
{
	char	**buf;
	char	*tmp;
	int		i;

	i = -1;
	buf = (char **)malloc(sizeof(char *) * (3));
	if (!buf)
		exit_ms("malloc rip", 1);
	i = -1;
	buf[0] = ft_strdup("export");
	if (!buf[0])
		exit_ms("malloc rip", 1);
	buf[1] = ft_strdup("PWD=");
	if (!buf[1])
		exit_ms("malloc rip", 1);
	tmp = (char *)malloc(sizeof(char) * 100);
	if (!tmp)
		exit_ms("malloc rip", 1);
	strapp(&buf[1], getcwd(tmp, 100), 2);
	if (!buf[1])
		exit_ms("malloc rip", 1);
	buf[2] = NULL;
	return (buf);
}

void	cd(char	*path, int index)
{
	void	*cp;
	int		error;

	if (!path)
		return ;
	cp = inf.pipes[index].cmd;
	if (access(path, F_OK) != 0)
	{
		ft_putendl_fd("not existing directory!", 2);
		return ;
	}
	error = chdir(path);
	if (!error)
	{
		inf.pipes[index].cmd = cp_cmd();
		export_main(index);
		return ;
	}
	perror(PERROR);
}

int	cd_main(char **cmd, int index)
{
	if (cmd && cmd[0] && cmd[1])
		cd(cmd[1], index);
	return (0);
}
