/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p1.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:59:20 by sdonny            #+#    #+#             */
/*   Updated: 2022/01/13 12:59:23 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate(int argc, char **argv)
{
	int	m;

	m = 0;
	if (ft_strncmp("here_doc", argv[1], 9) == 0)
		m = 1;
	if (argc < 4 + m)
	{
		ft_putstr_fd("Error!\nToo few arguments!\n", 2);
		exit(EXIT_FAILURE);
	}
	if (m)
	{
//		check_outfile(argv[argc - 1]);
		return (m);
	}
//	check_infile(argv[1], argv[argc - 1]);
	return (0);
}
