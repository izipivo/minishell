/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdursley <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:21:12 by pdursley          #+#    #+#             */
/*   Updated: 2022/08/21 10:22:15 by pdursley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

extern t_mshell	g_inf;

char	*parse_inf_key(char *s);
char	*parse_inf_val(char *s);

void	add_variable(t_env	*lenv, char **av)
{
	int	i;

	i = 0;
	while (lenv->next)
		lenv = lenv->next;
	while (av[++ i])
	{
		lenv->next = malloc(sizeof(t_env));
		if (!lenv->next)
			exit_ms("malloc", 1);
		lenv = lenv->next;
		lenv->key = parse_inf_key(av[i]);
		lenv->val = parse_inf_val(av[i]);
	}
	lenv->next = NULL;
}
