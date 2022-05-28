/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdpwdechoexit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:37:50 by sdonny            #+#    #+#             */
/*   Updated: 2022/04/26 15:18:46 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cd(char	*path)
{
	int	error;

	if (!path)
		return ;
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
