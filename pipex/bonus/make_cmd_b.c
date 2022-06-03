/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdursley <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 00:45:13 by pdursley          #+#    #+#             */
/*   Updated: 2022/03/31 00:45:13 by pdursley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	ft_error_make(t_pipex_b *pipex)
{
	ft_clean_main(*pipex);
	ft_clean_child(pipex);
	free(pipex->path);
	exit(1);
}

char	*make_cmd(t_pipex_b *pipex, char *av, char **command)
{
	char	*tmp;
	char	*comma;

	while (*command)
	{
		tmp = ft_strjoin(*command, "/");
		if (!tmp)
			ft_error_make(pipex);
		comma = ft_strjoin(tmp, av);
		if (!comma)
		{
			free(tmp);
			ft_error_make(pipex);
		}
		free(tmp);
		if (!(access(comma, 0)))
			return (comma);
		free(comma);
		command ++;
	}
	return (NULL);
}
