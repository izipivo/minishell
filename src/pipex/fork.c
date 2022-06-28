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
	// int		file;

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
	// char	*buf;
	// int		file;

	pipe = &inf.pipes[index];
	if (index && INPUT(pipe->mask) && pipe->in)
		child_in(pipe, index, fd);
	else if (index && HD(pipe->mask) && pipe->in)
		child_hd(pipe, index, fd);
	if (index + 1 != PIPES && pipe->out)
		child_out(pipe, index, fd, APP(pipe->mask));
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
			return (0);
	}
	else if (!(ft_strncmp(pipes->cmd[0], "env", 4)))
	{
		if (!parent)
			return (env_main());
		else
			return (0);
	}
	else if (!(ft_strncmp(pipes->cmd[0], "unset", 7)))
	{
		if (parent)
			return (unset_main(index));
		else
			return (0);
	}
	else if (!(ft_strncmp(pipes->cmd[0], "exit", 5)))
	{
		if (parent)
			exit_main(index);
		else
			return (0);
	}
	return (-1);
}

///////////////////////////////////////////////////////
void	free_env_copy(char **env)
{
	int i;

	i = -1;
	while (env[++ i])
		free(env[i]);
	free(env);
}
///////////////////////////////////////////////////////

char	**rebuild_env_copy(void)
{
	int i;
	char **env_copy;
	char *free_copy;
	void *tmp;

	i = 0;
	tmp = inf.lenv;
	while (inf.lenv)
	{
		i ++;
		inf.lenv = inf.lenv->next;
	}
	inf.lenv = tmp;
	env_copy = (char **)malloc(sizeof(char *) * i + 1);
	if (!env_copy)
		exit_ms(NULL, 0);
	env_copy[i] = 0;
	i = 0;
	while (inf.lenv)
	{
		env_copy[i] = ft_strdup(inf.lenv->key);
		free_copy = env_copy[i];
		env_copy[i] = ft_strjoin(env_copy[i], "=");
		free(free_copy);
		free_copy = env_copy[i];
		env_copy[i] = ft_strjoin(env_copy[i], inf.lenv->val);
		free(free_copy);
		i ++;
	}
	return (env_copy);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
int	update_env()
{
	if (!UPDATELENV(inf.mask))		// int.lenv изменился? если да то пересобираем inf.env_cpy иначе ретерн 0
		return (0);
	else
	{
		free_env_copy(inf.env_cpy);
		inf.env_cpy = rebuild_env_copy();
	}
	inf.mask &= ~(1 << 4);
	return (1);
}

int	child(int **fd, t_pipes *pipes, int index)
{
	char	**cmd;
	int		exit_status;

	child_fd(index, fd);
	close_fd(index, fd);
	exit_status = check_func(pipes, 0, index);
	if (exit_status != -1)
		exit(exit_status);
	cmd = cmdparse(pipes->cmd, inf.env, fd);
	if (!cmd[0])
		exitpipex(fd, "bin not found");
	if (update_env() && execve(cmd[0], cmd, inf.env_cpy) == -1)
		exitpipex(fd, cmd[0]);
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
			exitpipex(fd, "fork");
		else if (!pid[m])
			child(fd, pipes, m);
		// printf("forks: %p %s\n", pipes->cmd, pipes->cmd[1]);
		check_func(pipes, 1, m);
		pipes = pipes->next;
	}
	return (pid);
}
