/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdursley <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 00:40:27 by pdursley          #+#    #+#             */
/*   Updated: 2022/03/31 00:40:27 by pdursley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_child_one(t_pipex *pipex, char **av, char **envp)
{
	if (dup2(pipex->in, 0) < 0)
	{
		ft_clean_main(*pipex);
		ft_exit(*pipex);
	}
	close(pipex->pip[0]);
	if (dup2(pipex->pip[1], 1) < 0)
	{
		ft_clean_main(*pipex);
		ft_exit(*pipex);
	}
	pipex->split_command = ft_split(av[2], ' ');
	if (!pipex->split_command)
	{
		ft_clean_main(*pipex);
		ft_exit(*pipex);
	}
	pipex->result = make_cmd(pipex, pipex->split_command[0], pipex->command);
	if (!pipex->result)
	{
		ft_clean_child(pipex);
		write(2, "\nCommand not found\n", 19);
		exit(1);
	}
	ft_execve(pipex, envp);
}

void	ft_child_two(t_pipex *pipex, char **av, char **envp)
{
	if (dup2(pipex->out, 1) < 0)
	{
		ft_clean_main(*pipex);
		ft_exit(*pipex);
	}
	close(pipex->pip[1]);
	if (dup2(pipex->pip[0], 0) < 0)
	{
		ft_clean_main(*pipex);
		ft_exit(*pipex);
	}
	pipex->split_command = ft_split(av[3], ' ');
	if (!pipex->split_command)
	{
		ft_clean_main(*pipex);
		ft_exit(*pipex);
	}
	pipex->result = make_cmd(pipex, pipex->split_command[0], pipex->command);
	if (!pipex->result)
	{
		ft_clean_child(pipex);
		write(2, "\nCommand not found\n", 19);
		exit(1);
	}
	ft_execve(pipex, envp);
}
