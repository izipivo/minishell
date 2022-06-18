/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdpwdechoexit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:37:50 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/11 12:43:17 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char	*path)
{
	int	error;

	if (!path)
		return ;
	if (access(path, F_OK) != 0)
	{
		ft_putendl_fd("not existing directory!", 2);
		return ;
	}
	error = chdir(path);
	if (!error)
		return ;
	perror(PERROR);
}

int	main(int argc, char **argv)
{
	if (argc > 1)
		cd(argv[1]);
	return (0);
}
