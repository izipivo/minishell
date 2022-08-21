/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdursley <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:21:12 by pdursley          #+#    #+#             */
/*   Updated: 2022/08/21 10:22:15 by pdursley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen_env(char *en)
{
	int	i;

	i = 0;
	while (en[i])
		i ++;
	return (i);
}

void	print_exp(char **exp)
{
	int	i;

	i = -1;
	while (exp[++ i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(exp[i], 1);
		ft_putstr_fd("\n", 1);
	}
}

void	free_exp(char **exp)
{
	int	i;

	i = 0;
	while (exp[i])
	{
		free(exp[i]);
		i ++;
	}
	free(exp);
}

int	check_val(char c)
{
	if (c == '\0')
		return (0);
	if (c == 33 || c == 40 || c == 41)
		return (1);
	return (-1);
}

char	*one_c(char *c, int flag)
{
	if (flag == 1)
	{
		c = malloc(sizeof(char));
		if (!c)
			exit_ms("error malloc", -1);
		c[0] = '\0';
		return (c);
	}
	else
	{
		c = malloc(sizeof(char) + 1);
		if (!c)
			exit_ms("error malloc", -1);
		c[0] = '=';
		c[1] = '\0';
		return (c);
	}
}
