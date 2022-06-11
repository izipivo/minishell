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

#include "../includes/pipex.h"

static int	open_outfile(char *filename)
{
	if (!ft_strncmp("/", filename, 2))
		return (1);
	if (!ft_strncmp("\\/", filename, 2))
		return (open(filename + 2, O_APPEND | O_CREAT | O_WRONLY, 0664));
	if (access(filename, F_OK) == 0)
	{
		if (unlink(filename) == -1)
			return (-1);
	}
	return (open(filename, O_WRONLY | O_CREAT, 0664));
}
int	ifheredoc(char *filename)
{
	if (!ft_strncmp("//", filename, 2))
		return (2);
	return (0);
}

int	parentread(int fd, char *filename)
{
	char	*buf;
	int		file;
	int		cmp;

	file = 0;
	cmp = ifheredoc(filename);
	if (!cmp && !ft_strncmp("/", filename, 2))
		return (0);
	if (!cmp)
	{
//		ft_putendl_fd(filename, 1);
		file = open(filename, O_RDONLY);
//		ft_putnbr_fd(file, 1);
	}
	if (file == -1)
		return (-1);
	while (1)
	{
		buf = get_next_line(file);
		if (!buf)
			break ;
		if (cmp && ft_strncmp(buf, filename + cmp, ft_strlen(filename + cmp)) == 0)
		{
			free(buf);
			break ;
		}
		ft_putstr_fd(buf, fd);
		free(buf);
	}
	close(fd);
	if (!cmp)
		close(file);
	return (0);
}

int	parentwrite(int fd, char *filename, int flag)
{
	char	*buf;
	int		file;

	file = 1;
    file = open_outfile(filename);
//	if (!flag && ft_strncmp("/", filename, 2))
//	{
//		ft_putstr_fd("otkrivet file: ", 1);
//        ft_putendl_fd(filename, 1);
//		file = rmandopen(filename);
//	}
//	else if (ft_strncmp("/", filename, 2))
//	{
//        ft_putstr_fd("otkrivet file: ", 1);
//        ft_putendl_fd(filename, 1);
//		file = open(filename, O_APPEND | O_CREAT | O_WRONLY, 0664);
//	}
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
	close(file);
	return (0);
}

void	waitchildren(pid_t *pid, int **fd, int argc)
{
	int	m;

	m = -1;
	while (++m < argc)
	{
		if (waitpid(pid[m], NULL, 0) == -1)
			exitpid(fd, pid, "waitpid()");
		free(fd[m]);
	}
	free(fd[m]);
	free(fd);
	free(pid);
}
