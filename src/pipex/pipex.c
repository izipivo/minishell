/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:06:53 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/11 16:02:06 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_mshell	g_inf;

char	*check_buildin(char *pwd, char *tmp)
{
	char	*buf;
	char	*buf2;

	buf = ft_strjoin(pwd, "/bin/");
	buf2 = ft_strjoin(buf, tmp);
	if (buf)
		free(buf);
	if (access(buf2, F_OK) == 0)
		return (buf2);
	free(buf2);
	return (NULL);
}

char	*findpathh(char **paths, char *path, int **fd, char *tmp)
{
	int		i;
	char	*slesh;

	i = -1;
	while (paths[++i])
	{
		slesh = ft_strjoin(paths[i], "/");
		path = ft_strjoin(slesh, tmp);
		free(slesh);
		if (access(path, F_OK) == 0)
		{
			cleansplit(paths);
			free(tmp);
			return (path);
		}
		free(path);
	}
	cleansplit(paths);
	exitpipex(fd, tmp);
	return (NULL);
}

char	*checkpath(char *tmp, char **envp, int **fd)
{
	char	**paths;
	char	*path;
	int		i;

	i = -1;
	if (access(tmp, F_OK) == 0)
		return (tmp);
	while (ft_strnstr(envp[++i], "PWD", 4) == 0)
		;
	path = check_buildin(&envp[i][4], tmp);
	if (path)
	{
		free(tmp);
		return (path);
	}
	i = -1;
	while (ft_strnstr(envp[++i], "PATH", 4) == 0)
		;
	paths = ft_split(envp[i] + 5, ':');
	return (findpathh(paths, path, fd, tmp));
}

static int	**multipipe(int m)
{
	int	i;
	int	**fd;

	fd = (int **)malloc(sizeof(int *) * m);
	if (!fd)
		exitmalloc(fd);
	i = -1;
	while (++i < m)
	{
		fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!fd[i])
			exitmalloc(fd);
		if (pipe(fd[i]) == -1)
			exitmalloc(fd);
	}
	return (fd);
}

int	pipex(void)
{
	int		**fd;
	pid_t	*pid;

	fd = multipipe((g_inf.mask >> 16) + 1);
	pid = forks(fd);
	close_all(fd);
	waitchildren(pid, fd, (g_inf.mask >> 16));
	return (0);
}
