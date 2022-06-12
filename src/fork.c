/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:59:08 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/11 15:20:12 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

extern t_mshell inf;

static char	**cmdparse(char **new, char **envp)
{
	char	*tmp;

	tmp = new[0];
	new[0] = checkpath(tmp, envp);
	free(tmp);
	tmp = NULL;
	return (new);
}

static void	killchild(char **cmd, int **fd)
{
	cleansplit(cmd);
	close(0);
	close(1);
	exit(EXIT_SUCCESS);
}

static pid_t	*createpids(int **fd)
{
	pid_t	*pid;

	// printf("__createpids__ %d pipe(s)\n", PIPES);
	pid = (pid_t *)malloc(sizeof(pid_t) * PIPES);
	if (!pid)
		exitmalloc(fd);
	return (pid);
}

void	child_hd(t_pipes *pipe, int index, int **fd)
{
	char	*buf;

	while (1)
	{
		buf = get_next_line(0);
		if (!buf)
			break ;
		// printf("b: %s\ni: %s\nbl: %d il: %d\n", buf, pipe->in, ft_strlen(buf), ft_strlen(pipe->in));
		if (ft_strncmp(buf, pipe->in, ft_strlen(pipe->in)) == 0)
		{
			free(buf);
			break ;
		}
		ft_putstr_fd(buf, fd[index][1]);
		free(buf);
	}
}

void	child_in(t_pipes *pipe, int index, int **fd)
{
	int		file;

	printf("est' infile\n");
	fd[index][0] = open(pipe->in, O_RDONLY);
	if (fd[index][0] < 0)
	{
		ft_putendl_fd("not valid infile", 2);
		exit(228);
		//exit_pipex();
	}
}

void	child_out(t_pipes *pipe, int index, int **fd, int app)
{
	printf("est' outfile\n");
	if (!app && access(pipe->out, F_OK) == 0)
	{
		if (unlink(pipe->out) == -1)
			exit(1488);
	}
	if (!app)
		fd[index + 1][1] = open(pipe->out, O_RDONLY);
	else
		fd[index + 1][1] = open(pipe->out, O_APPEND | O_CREAT | O_WRONLY, 0664);
	if (fd[index + 1][1] < 0)
	{
		ft_putendl_fd("not valid outfile", 2);
		exit(322);
		//exit_pipex();
	}
}

void	child_fd(int index, int **fd)
{
	t_pipes	*pipe;
	char	*buf;
	int		file;

	pipe = &inf.pipes[index];
	if (index && INPUT(pipe->mask) && pipe->in)
		child_in(pipe, index, fd);
	else if (index && HD(pipe->mask) && pipe->in)
		child_hd(pipe, index, fd);
	if (index + 1 != PIPES && pipe->out)
		child_out(pipe, index, fd, APP(pipe->mask));
}

int	child(int **fd, pid_t *pid, t_pipes *pipes, int index)
{
	char	**cmd;

	child_fd(index, fd);
	close_fd(index, fd);
	cmd = cmdparse(pipes->cmd, inf.env);
	if (!cmd[0])
		exitcmd(fd, pid, cmd);
	if (execve(cmd[0], cmd, inf.env) == -1)
		exitpid(fd, pid, "execve rip");
	killchild(cmd, fd);
	return (1);
}

pid_t	*forks(int **fd)
{
	int		m;
	pid_t	*pid;
	t_pipes	*pipes;

	m = -1;
	pipes = inf.pipes;
	pid = createpids(fd);
	while (pipes)
	{
		pid[++m] = fork();
		if (pid[m] < 0)
			exitpid(fd, pid, "fork");
		if (!pid[m])
			child(fd, pid, pipes, m);
		pipes = pipes->next;
	}
	return (pid);
}
