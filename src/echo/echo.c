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

/*
 *		!!! echo $... !!!
 */

void	echo(char *string, int n)
{
	if (n)
		ft_putstr_fd(string, 1);
	else
		ft_putendl_fd(string, 1);
}

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		ft_putstr_fd(PERROR": too few arguments!\n", 2);
		return (1);
	}
	if (argc == 2)
		echo(argv[1], 0);
	else if (ft_strncmp("-n", argv[1], 3) == 0)
		echo(argv[2], 1);
	else
		echo(argv[2], 0);
	return (0);
}
