/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parents.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:59:30 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/11 15:16:05 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_mshell	inf;

int	open_outfile(char *filename, int app)
{
	if (!inf.pipes[PIPES - 1].out)
		return (1);
	if (app)
		return (open(filename, O_APPEND | O_CREAT | O_WRONLY, 0664));
	if (access(filename, F_OK) == 0)
	{
		if (unlink(filename) == -1)
			return (-1);
	}
	return (open(filename, O_WRONLY | O_CREAT, 0664));
}

int	parentread(int fd, char *filename, int hd)
{
	char	*buf;
	int		file;

	file = 0;
	if (!hd)
		file = open(filename, O_RDONLY);
	if (file == -1)
		return (-1);
	while (1)
	{
		buf = get_next_line(file);
		if (!buf)
			break ;
		if (hd && ft_strncmp(buf, filename, ft_strlen(filename)) == 0)
		{
			free(buf);
			break ;
		}
		ft_putstr_fd(buf, fd);
		free(buf);
	}
	close(fd);
	if (!hd)
		close(file);
	return (0);
}

int	parentwrite(int fd, char *filename, int app)
{
	char	*buf;
	int		file;

	file = 1;
	file = open_outfile(filename, app);
	if (file == -1)
		return (-1);
	while (1)
	{
		buf = get_next_line(fd);
		if (!buf)
			break ;
		ft_putstr_fd(buf, file);
		free(buf);
	}
	close(fd);
	if (file != 1)
		close(file);
	return (0);
}

void	waitchildren(pid_t *pid, int **fd, int argc)
{
	int	m;

	m = -1;
	while (++m < argc)
	{
		if (pid[m] != -228 && (waitpid(pid[m], NULL, 0) == -1))
			exitpipex(fd, "waitpid()");
		free(fd[m]);
	}
	free(fd[m]);
	free(fd);
	free(pid);
}
