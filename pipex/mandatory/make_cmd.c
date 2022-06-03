/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdursley <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 00:40:10 by pdursley          #+#    #+#             */
/*   Updated: 2022/03/31 00:40:10 by pdursley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_error_make(t_pipex *pipex)
{
	ft_clean_main(*pipex);
	ft_clean_child(pipex);
	free(pipex->path);
}

char	*make_cmd(t_pipex *pipex, char *av, char **command)
{
	char	*tmp;

	while (*command)
	{
		tmp = ft_strjoin(*command, "/");
		if (!tmp)
		{
			ft_error_make(pipex);
			ft_exit(*pipex);
		}	
		pipex->cmd = ft_strjoin(tmp, av);
		if (!pipex->cmd)
		{
			free(tmp);
			ft_error_make(pipex);
			ft_exit(*pipex);
		}
		free(tmp);
		if (!(access(pipex->cmd, 0)))
			return (pipex->cmd);
		free(pipex->cmd);
		command ++;
	}
	return (NULL);
}
