/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdursley <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 00:45:36 by pdursley          #+#    #+#             */
/*   Updated: 2022/03/31 00:45:36 by pdursley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	ft_dup(int fd1, int fd2, t_pipex_b *pipex)
{
	if (dup2(fd1, 0) < 0)
	{
		ft_clean_main(*pipex);
		free(pipex->path);
		exit(1);
	}
	if (dup2(fd2, 1) < 0)
	{
		ft_clean_main(*pipex);
		free(pipex->path);
		exit(1);
	}
}

void	check_command(t_pipex_b *pipex)
{
	if (!pipex->command)
	{
		ft_clean_main(*pipex);
		free(pipex->path);
		exit(1);
	}
}

void	ft_error(t_pipex_b *pipex)
{
	ft_close(pipex);
	if (pipex->here_doc == 1)
		unlink(".heredoc_tmp");
	if (pipex->pip)
		free(pipex->pip);
	if (pipex->path)
		free(pipex->path);
	exit(1);
}

void	create_pipe(t_pipex_b *pipex_b)
{
	int	i;

	i = 0;
	while (i < (pipex_b->pipe_num - 1))
	{
		if (pipe(pipex_b->pip + 2 * i) < 0)
			ft_clean_main(*pipex_b);
		i ++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex_b	pipex_b;

	pipex_b.num_child = -1;
	infile(&pipex_b, argv, argc);
	outfile(&pipex_b, argv, argc);
	pipex_b.number_cmd = argc - 3 - pipex_b.here_doc;
	pipex_b.pipe_num = 2 * (pipex_b.number_cmd - 1);
	pipex_b.pip = (int *)malloc(sizeof(int) * pipex_b.pipe_num);
	if (!pipex_b.pip)
		ft_error(&pipex_b);
	pipex_b.path = ft_parse_path(envp);
	if (!pipex_b.path)
		ft_error(&pipex_b);
	pipex_b.command = ft_split(pipex_b.path, ':');
	check_command(&pipex_b);
	create_pipe(&pipex_b);
	while (++ (pipex_b.num_child) < pipex_b.number_cmd)
		ft_child(&pipex_b, argv, envp);
	ft_close_pip(&pipex_b);
	waitpid(-1, NULL, 0);
	ft_clean_main(pipex_b);
	return (0);
}
