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
	// free(tmp);
	// tmp = NULL;
	return (new);
}

static void	killchild(char **cmd, int **fd)
{
	// cleansplit(cmd);
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
		exitpipex(fd, pipe->in);
	}
}

void	child_out(t_pipes *pipe, int index, int **fd, int app)
{
	printf("est' outfile\n");
	if (!app && access(pipe->out, F_OK) == 0)
	{
		if (unlink(pipe->out) == -1)
			exitpipex(fd, pipe->out);
	}
	if (!app)
		fd[index + 1][1] = open(pipe->out, O_RDONLY);
	else
		fd[index + 1][1] = open(pipe->out, O_APPEND | O_CREAT | O_WRONLY, 0664);
	if (fd[index + 1][1] < 0)
		exitpipex(fd, pipe->out);
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
	cmd = cmdparse(pipes->cmd, inf.env, fd);
	if (!cmd[0])
		exitpipex(fd, "bin not found");
	if (execve(cmd[0], cmd, inf.env) == -1)
		exitpipex(fd, cmd[0]);
	killchild(cmd, fd);
	return (1);
}

int	check_func(t_pipes *pipes)
{
	if (!(ft_strncmp(pipes->cmd[0], "export", 8)))
		export_main();
	else if (!(ft_strncmp(pipes->cmd[0], "unset", 7)))
		unset_main();
	// else if (!(ft_strncmp(pipes->cmd[0], "echo", 5)))
	// 	echo_main();
	else if (!(ft_strncmp(pipes->cmd[0], "env", 4)))
		env_main();
	else
		return (0);
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
		if (check_func(pipes))
		{
			pid[++ m] = fork();
			if (pid[m] < 0)
				exitpipex(fd, "fork");
			// if (!pid[m])
			// 	child(fd, pid, pipes, m);
			pipes = pipes->next;
			continue;
		}
		pid[++ m] = fork();
		if (pid[m] < 0)
			exitpipex(fd, "fork");
		if (!pid[m])
			child(fd, pid, pipes, m);
		pipes = pipes->next;
	}
	return (pid);
}
