/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdursley <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 00:44:46 by pdursley          #+#    #+#             */
/*   Updated: 2022/03/31 00:44:46 by pdursley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	ft_error_in_out(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

void	outfile(t_pipex_b *pipex, char **av, int ac)
{
	if (pipex->here_doc == 1)
		pipex->out = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
	{
		if (!ft_strncmp("/", av[ac - 1], 2))
		{
			pipex->out = 1;
			return;
		}
		pipex->out = open(av[ac - 1], O_RDWR | O_TRUNC | O_CREAT, 0777);
	}
	if (pipex->out < 0)
	{
		if (pipex->here_doc == 0)
		{
			if (unlink(av[1]) < 0)
				ft_error_in_out("Can not unlink .here_doc!");
		}
		ft_error_in_out("Can not open: outfile!");
	}
}

void	infile(t_pipex_b *pipex, char **av, int ac)
{
	if (!ft_strncmp(av[1], "here_doc", 9))
	{
		if (ac >= 6)
		{
			pipex->here_doc = 1;
			check_heredoc(pipex, av);
		}
		else
			ft_error_in_out("ac < 6!");
	}
	else
	{
		if (ac >= 5)
		{
			pipex->here_doc = 0;
			if (!ft_strncmp("/", av[1], 2))
			{
				pipex->in = 0;
				return ;
			}
			pipex->in = open(av[1], O_RDONLY);
			if (pipex->in < 0)
				ft_error_in_out("Can not open: infile!");
		}
		else
			ft_error_in_out("ac < 5");
	}
}
