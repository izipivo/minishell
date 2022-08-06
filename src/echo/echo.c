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

#include "minishell.h"

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

int	echo_main(int argc, char **argv)
{
	int	f;
	int	i;

	f = 0;
	i = 0;
	if (argc == 1)
	{
		ft_putchar_fd('\n', 2);
		return (0);
	}
	while (argv[++i] && !ft_strncmp("-n", argv[i], 2))
		f = 1;
	echo(&argv[i], f);
	return (0);
}
