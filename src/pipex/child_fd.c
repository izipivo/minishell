/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:59:08 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/11 15:20:12 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_mshell	g_inf;

static void	child_hd(t_pipes *pipe, int index, int **fd)
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

static void	child_in(t_pipes *pipe, int index, int **fd)
{
	fd[index][0] = open(pipe->in, O_RDONLY);
	if (fd[index][0] < 0)
	{
		ft_putendl_fd("not valid infile", 2);
		exitpipex(fd, pipe->in);
	}
}

static void	child_out(t_pipes *pipe, int index, int **fd, int app)
{
	if (!app && pipe->out && access(pipe->out, F_OK) == 0)
	{
		if (unlink(pipe->out) == -1)
			exitpipex(fd, pipe->out);
	}
	if (!app && pipe->out)
		fd[index + 1][1] = open(pipe->out, O_WRONLY | O_CREAT, 0664);
	else if (app && pipe->out)
		fd[index + 1][1] = open(pipe->out, O_APPEND | O_CREAT | O_WRONLY, 0664);
	else if (!pipe->out && index == (g_inf.mask >> 16) - 1)
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
	while (++i <= (g_inf.mask >> 16))
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

	pipe = &g_inf.pipes[index];
	if (pipe->in && pipe->mask & 1)
		child_in(pipe, index, fd);
	else if (pipe->in && !(pipe->mask & 1))
		child_hd(pipe, index, fd);
	if (!index && !pipe->in)
		close(fd[index][0]);
	else
	{
		dup2(fd[index][0], STDIN_FILENO);
		close(fd[index][0]);
	}
	child_out(pipe, index, fd, !(pipe->mask >> 1 & 1));
	close_all(fd);
}
