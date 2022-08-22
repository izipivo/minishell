/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:37:50 by sdonny            #+#    #+#             */
/*   Updated: 2022/04/26 15:18:46 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		perror(PERROR);
		return (1);
	}
	ft_putendl_fd(path, 1);
	free(path);
	return (0);
}

int	pwd_main(void)
{
	return (pwd());
}
