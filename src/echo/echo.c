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

void	echo(char **string, int n)
{
	while (*string)
	{
		ft_putstr_fd(*string, 1);
		if (*(++string))
			ft_putchar_fd(' ', 1);
	}
	if (!n)
		ft_putchar_fd('\n', 1);
}

int main(int argc, char **argv)
{
	if (argc == 1)
		ft_putchar_fd('\n', 2);
	else if (ft_strncmp("-n", argv[1], 2) == 0)
		echo(argv + 2, 1);
	else
		echo(argv + 1, 0);
	return (0);
}
