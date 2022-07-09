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

// #include "minishell.h"

// void	cd(char	*path)
// {
// 	int	error;

// 	if (!path)
// 		return ;
// 	if (access(path, F_OK) != 0)
// 	{
// 		ft_putendl_fd("not existing directory!", 2);
// 		return ;
// 	}
// 	error = chdir(path);
// 	if (!error)
// 		return ;
// 	perror(PERROR);
// }

// int	main(int argc, char **argv)
// {
// 	if (argc > 1)
// 		cd(argv[1]);
// 	return (0);
// }

#include "minishell.h"

extern t_mshell	inf;

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
	inf.pipes[index].cmd = cp_oldpwd();
	error = chdir(path);
	if (!error)
	{
		export_main(index);
		free_strs(inf.pipes[index].cmd);
		inf.pipes[index].cmd = cp_cmd();
		export_main(index);
		free_strs(inf.pipes[index].cmd);
	}
	else
		perror(PERROR);
	inf.pipes[index].cmd = (char **)cp;
}

int	cd_main(char **cmd, int index)
{
	if (cmd && cmd[0] && cmd[1])
		cd(cmd[1], index);
	return (0);
}