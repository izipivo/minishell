/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_managment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:58:59 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/11 15:36:27 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_mshell	inf;

void *free_fd(int **fd)
{
	int	i;

	i = -1;
	if (fd)
	{
		while (++i <= PIPES)
		{
			if (fd[i])
				free(fd[i]);
		}
		free(fd);
		fd = NULL;
	}
	return (NULL);
}

void	exitmalloc(int **fd)
{
	perror("malloc rip");
	fd = free_fd(fd);
	ft_putendl_fd("pipex gone mad", 2);
	exit(43);
}

void	exitpipex(int **fd, char *desc)
{
	// int	i;

	// i = -1;
	// if (cmd)
	// 	cleansplit(cmd);
	perror(desc);
	fd = free_fd(fd);
	free(inf.pids);
	inf.pids = NULL;
	free_pipes(inf.pipes);
	exit(22);
}
