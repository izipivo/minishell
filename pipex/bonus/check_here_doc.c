/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdursley <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 00:43:12 by pdursley          #+#    #+#             */
/*   Updated: 2022/03/31 00:43:18 by pdursley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	ft_unlink(t_pipex_b *pipex)
{
	if (pipex->in < 0)
	{
		unlink(".heredoc_tmp");
		exit(1);
	}
}

void	check_heredoc(t_pipex_b *pipex, char **av)
{
	char	*line;
	int		fd_here_doc;
	char	*flag;

	fd_here_doc = open(".heredoc_tmp", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd_here_doc < 0)
		exit(1);
	while (1)
	{
		flag = get_next_line(0, &line);
		if (!flag)
			return ;
		if (ft_strlen(av[2]) == -1 + ft_strlen(line)
			&& (!(ft_strncmp(av[2], line, ft_strlen(av[2])))))
			break ;
		write(fd_here_doc, flag, ft_strlen(flag));
		free(flag);
	}
	free(line);
	close(fd_here_doc);
	pipex->in = open(".heredoc_tmp", O_RDONLY, 0777);
	if (!pipex->in)
		exit(1);
}
