/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdursley <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 00:44:19 by pdursley          #+#    #+#             */
/*   Updated: 2022/03/31 00:44:19 by pdursley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	ft_execve(t_pipex_b *pipex, char **envp)
{
	if (execve(pipex->cmd, pipex->split_command, envp) < 0)
	{
		ft_clean_main(*pipex);
		ft_clean_child(pipex);
		free(pipex->path);
		ft_putendl_fd("execve rip :(", 2);
		exit(1);
	}
}

void	ft_error_split_command(t_pipex_b *pipex)
{
	ft_clean_main(*pipex);
	free(pipex->path);
	ft_error_in_out("ft_split can not split your args!");
}

void	ft_clean_child(t_pipex_b *pipex)
{
	int	i;

	i = -1;
	while (pipex->split_command[++ i])
		free(pipex->split_command[i]);
	free(pipex->split_command);
	free(pipex->cmd);
}

void	ft_child(t_pipex_b *pipex, char **argv, char **envp)
{
	pipex->all_pid = fork();
	if (pipex->all_pid == 0)
	{
		if (pipex->num_child == 0)
			ft_dup(pipex->in, pipex->pip[1], pipex);
		else if (pipex->num_child == pipex->number_cmd - 1)
			ft_dup(pipex->pip[2 * pipex->num_child - 2], pipex->out, pipex);
		else
			ft_dup(pipex->pip[2 * pipex->num_child - 2],
				pipex->pip[2 * pipex->num_child + 1], pipex);
		ft_close_pip(pipex);
		pipex->split_command
			= ft_split(argv[2 + pipex->here_doc + pipex->num_child], ' ');
		if (!pipex->split_command)
			ft_error_split_command(pipex);
		pipex->cmd = make_cmd(pipex, pipex->split_command[0], pipex->command);
		if (!pipex->cmd)
		{
			ft_clean_child(pipex);
			write(2, "\nCommand not found\n", 19);
			exit(1);
		}
		ft_execve(pipex, envp);
	}
}
