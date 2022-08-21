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

extern t_mshell	g_inf;

int	open_(char *filename, int app)
{
	if (!g_inf.pipes[(g_inf.mask >> 16) - 1].out)
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

void	waitchildren(pid_t *pid, int **fd, int argc)
{
	int	m;
	int	status;

	m = -1;
	while (++m < argc)
	{
		if (pid[m] != -228 && (waitpid(pid[m], &status, 0) == -1))
			exitpipex(fd, "waitpid()");
		free(fd[m]);
	}
	if (!g_inf.code)
		g_inf.code = WEXITSTATUS(status);
	free(fd[m]);
	free(fd);
	free(pid);
}
