/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdursley <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 00:37:14 by pdursley          #+#    #+#             */
/*   Updated: 2022/03/31 00:37:18 by pdursley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_execve(t_pipex *pipex, char **envp)
{
	if (execve(pipex->result, pipex->split_command, envp) < 0)
	{
		ft_clean_main(*pipex);
		ft_clean_child(pipex);
		ft_exit(*pipex);
	}
}

void	check_path(t_pipex pipex)
{
	if (!pipex.path)
	{
		write(2, "\nError\n", 7);
		exit(1);
	}
}

void	ft_exit(t_pipex pipex)
{
	free(pipex.path);
	ft_close(&pipex);
	exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	ft_open_fd(&pipex, argv, argc);
	pipex.path = ft_parse_path(envp);
	check_path(pipex);
	if (pipe(pipex.pip) < 0)
		ft_exit(pipex);
	pipex.command = ft_split(pipex.path, ':');
	if (!pipex.command)
		ft_exit(pipex);
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		ft_clean_main(pipex);
	if (pipex.pid1 == 0)
		ft_child_one(&pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 < 0)
		ft_clean_main(pipex);
	if (pipex.pid2 == 0)
		ft_child_two(&pipex, argv, envp);
	ft_close(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	ft_clean_main(pipex);
	return (0);
}
