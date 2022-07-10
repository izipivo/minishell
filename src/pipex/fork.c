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

#include "minishell.h"

extern t_mshell inf;

static char	**cmdparse(char **new, char **envp, int **fd)
{
	char	*tmp;

	tmp = new[0];
	new[0] = checkpath(tmp, envp, fd);
	return (new);
}

static void	killchild(char **cmd, int **fd)
{
	// cleansplit(cmd);
	(void)cmd;
	(void)fd;
	free_pipes(inf.pipes);
	close(0);
	close(1);
	exit(EXIT_SUCCESS);
}

static pid_t	*createpids(int **fd)
{
	pid_t	*pid;
	int		i;

	i = -1;
	pid = (pid_t *)malloc(sizeof(pid_t) * PIPES);
	if (!pid)
		exitmalloc(fd);
	while (++i < PIPES)
		pid[i] = 0;
	inf.pids = pid;
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
	fd[index][0] = open(pipe->in, O_RDONLY);
	if (fd[index][0] < 0)
	{
		ft_putendl_fd("not valid infile", 2);
		exitpipex(fd, pipe->in);
	}
}

void	child_out(t_pipes *pipe, int index, int **fd, int app)
{
	if (!app && pipe->out && access(pipe->out, F_OK) == 0)
	{
		if (unlink(pipe->out) == -1)
			exitpipex(fd, pipe->out);
	}
	if (!app && pipe->out)
		fd[index + 1][1] = open(pipe->out, O_WRONLY | O_CREAT);
	else if (app && pipe->out)
		fd[index + 1][1] = open(pipe->out, O_APPEND | O_CREAT | O_WRONLY, 0664);
	else if (!pipe->out && index == PIPES - 1)
	{
		close(fd[index + 1][1]);
		return ;
	}
	if (fd[index + 1][1] < 0)
		exitpipex(fd, pipe->out);
	dup2(fd[index + 1][1], STDOUT_FILENO);
	close(fd[index + 1][1]);
}

int	close_all(int **fd)
{
	int	i;
	int	j;

	i = -1;
	while (++i <= PIPES)
	{
		j = -1;
		while (++j < 2)
			close(fd[i][j]);
	}
	return (0);
}

void	child_fd(int index, int **fd)
{
	t_pipes	*pipe;

	pipe = &inf.pipes[index];
	if (pipe->in && INPUT(pipe->mask))
		child_in(pipe, index, fd);
	else if (pipe->in && HD(pipe->mask))
		child_hd(pipe, index, fd);
	if (!index && !pipe->in)
		close(fd[index][0]);
	else
	{
		dup2(fd[index][0], STDIN_FILENO);
		close(fd[index][0]);
	}
	child_out(pipe, index, fd, APP(pipe->mask));
	close_all(fd);
}

int	check_func(t_pipes *pipes, int parent, int index)
{
	if (!(ft_strncmp(pipes->cmd[0], "export", 8)))
	{
		if (parent && pipes->cmd[1])
			return (export_main(index));
		else if (!parent && !pipes->cmd[1])
			return (export_main(index));
		else
			return (256);
	}
	else if (!(ft_strncmp(pipes->cmd[0], "env", 4)))
	{
		if (!parent)
			return (env_main());
		else
			return (256);
	}
	else if (!(ft_strncmp(pipes->cmd[0], "unset", 7)))
	{
		if (parent)
			return (unset_main(index));
		else
			return (256);
	}
	else if (!(ft_strncmp(pipes->cmd[0], "exit", 5)))
	{
		if (parent)
			exit_main(index);
		else
			return (256);
	}
	else if (!(ft_strncmp(pipes->cmd[0], "cd", 5)))
	{
		if (parent)
			cd_main(pipes->cmd, index);
		else
			return (256);
	}
	return (256);
}

int	child(int **fd, t_pipes *pipes, int index)
{
	char	**cmd;
	int		exit_status;

	child_fd(index, fd);
	exit_status = check_func(pipes, 0, index);
	if (exit_status != 256)
		exit(exit_status);
	cmd = cmdparse(pipes->cmd, inf.env, fd);
	if (!cmd[0])
		exitpipex(fd, "bin not found");
	if (execve(cmd[0], cmd, inf.env) == -1)
		exitpipex(fd, cmd[0]);
	killchild(cmd, fd);
	return (1);
}

pid_t	*forks(int **fd)
{
	int		m;
	int		tmp;
	pid_t	*pid;
	t_pipes	*pipes;

	m = -1;
	pipes = inf.pipes;
	pid = createpids(fd);
	while (pipes)
	{
		pid[++m] = fork();
		if (pid[m] < 0)
			exitpipex(fd, "fork");
		else if (!pid[m])
			child(fd, pipes, m);
		tmp = check_func(pipes, 1, m);
		if (tmp != 256)
			inf.code = tmp;
		pipes = pipes->next;
	}
	return (pid);
}
