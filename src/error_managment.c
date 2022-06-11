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

#include "../includes/pipex.h"

void	exitmalloc(int **fd)
{
	int	i;
	int	quantity;

	i = -1;
	quantity = PIPES;
	perror("pipes\n");
	if (fd)
	{
		while (++i < quantity)
			free(fd[i]);
		free(fd);
		fd = NULL;
	}
	ft_putendl_fd("pipex gone mad", 2);
	exit(EXIT_FAILURE);
}

void	exitpid(int **fd, pid_t *pid, char *desc)
{
	int	i;
	int	quantity;

	i = -1;
	quantity = PIPES;
	perror(desc);
	while (++i < quantity + 1)
		free(fd[i]);
	free(fd);
	fd = NULL;
	free(pid);
	pid = NULL;
	exit(EXIT_FAILURE);
}

void	exitcmd(int **fd, pid_t *pid, char *cmd)
{
	char	**spl;
	int		quantity;

	quantity = PIPES;
	spl = ft_split(cmd, ' ');
	while (--quantity)
		free(fd[quantity]);
	free(fd);
	free(pid);
	ft_putstr_fd(spl[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	cleansplit(spl);
	exit(EXIT_FAILURE);
}
