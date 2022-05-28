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

#include "../includes/minishell.h"

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

void	pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		perror(PERROR);
		return ;
	}
	printf("%s\n", path);
	free(path);
}

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

/*
 *		Команда выхода из минишелла
 */
//void	exit()
//{
//}

//int	main(int argc, char **argv)
//{
//	if (argc > 1)
//		cd(argv[1]);
//	pwd();
//	echo(argv[2], 0);
//	return (228);
//}
