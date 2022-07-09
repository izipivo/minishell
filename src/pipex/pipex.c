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

extern t_mshell	inf;

void	cleansplit(char **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
		free(cmd[i]);
	free(cmd);
	cmd = NULL;
}

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

char	*checkpath(char *tmp, char **envp, int **fd)
{
	char	**paths;
	char	*path;
	char	*slesh;
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
	// free(tmp);
	return (NULL);
}

void	close_fd(int proc, int **fd)
{
	int	i;
	int	j;

	i = -1;
	while (++i < PIPES + 1)
	{
		j = -1;
		while (++j < 2)
		{
			if ((i == proc && j == 0) || (i == proc + 1 && j == 1)
				|| (((i == PIPES && j == 0) || (i == 0 && j == 1))
					&& proc == -1))
				continue ;
			close(fd[i][j]);
		}
	}
	if (proc >= 0)
	{
		dup2(fd[proc][0], 0);
		close(fd[proc][0]);
		dup2(fd[proc + 1][1], 1);
		close(fd[proc + 1][1]);
	}
}

static int	**multipipe(int m)
{
	int	i;
	int	**fd;

	fd = (int **)malloc(sizeof(int *) * m);
	if (!fd)
		exitmalloc( fd);
	i = -1;
	while (++i < m)
	{
		fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!fd[i])
			exitmalloc( fd);
		if (pipe(fd[i]) == -1)
			exitmalloc(fd);
	}
	return (fd);
}

int	pipex(void)
{
	int		**fd;
	// int		check;
	pid_t	*pid;

	fd = multipipe(PIPES + 1);
	pid = forks(fd);
	close_fd(-1, fd);
	if (inf.pipes[0].in)
		// check = 
		parentread(fd[0][1], inf.pipes[0].in, HD(inf.pipes[0].mask));
	else
	{
		dup2(0, fd[0][0]);
		// close(0);
	}
	//if (check == -1)
	//	exitpid(fd, pid, argc, "parentread");
	// check = 
	parentwrite(fd[PIPES][0], inf.pipes[PIPES - 1].out, APP(inf.pipes[PIPES - 1].mask));
	// close_all(fd);
	// if (check == -1)
	// 	exitpid(fd, pid, argc, "parentwrite");
	waitchildren(pid, fd, PIPES);
	return (0);
}
