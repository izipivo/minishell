/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 15:32:12 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/12 15:14:55 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_mshell	inf;

t_pipes	*copy_pipes(t_pipes *new, t_list *old)
{
	int		i;
	int		j;

	j = -1;
	i = 0;
	while (old)
	{
		if (old->key == PIPE)
		{
			cap(new, i, ++j);
			ft_memset(&new[++i], 0, sizeof(t_pipes));
			new[i].cmd = (char **) malloc(sizeof(char *) * q_args(old));
			if (!new->cmd)
				exit_ms("malloc rip", 1);
			j = -1;
		}
		else if (old->key > 2 && old->key < 5)
			copy_in(&new[i], old->val, old->key);
		else if (old->key > 4 && old->key < 7)
			copy_out(&new[i], old->val, old->key);
		else if (old->key == COMMAND)
			j += copy_word(&new[i], j, old);
		old = old->next;
	}
	return (end_pipes(new, i, j));
}

t_pipes	*remalloc(void)
{
	t_list	*old;
	t_pipes	*new;

	old = inf.tokens;
	if (old->key == PIPE)
		return (stop_exec(NULL));
	inf.mask = count_pipes(old) << 16;
	new = (t_pipes *) malloc(sizeof(t_pipes) * (PIPES + 1));
	if (!new)
		exit_ms("malloc rip", 1);
	ft_memset(&new[0], 0, sizeof(t_pipes));
	new[0].cmd = (char **) malloc(sizeof(char *) * q_args(old));
	if (!new[0].cmd)
		exit_ms("malloc rip", 1);
	return (copy_pipes(new, old));
}

void	strapp(char **s1, char *s2, int f)
{
	char	*str;

	str = *s1;
	if (!str && !s2)
		return ;
	if (!str)
	{
		*s1 = ft_strdup(s2);
	}
	else if (s2)
	{
		*s1 = ft_strjoin(str, s2);
		if (f)
		{
			free(str);
			str = NULL;
		}
	}
	if (f == 2)
	{
		free(s2);
		s2 = NULL;
	}
	if (!(*s1))
		exit_ms("malloc", 1);
}

char	*find_env(char *find)
{
	t_env	*lenv;
	char	*found;

	lenv = inf.lenv;
	if (!*find)
		return (NULL);
	while (lenv)
	{
		if (!ft_strncmp(lenv->key, find, ft_strlen(find)))
		{
			found = ft_strdup(lenv->val);
			if (!found)
				exit_ms(NULL, 1);
			return (found);
		}		
		lenv = lenv->next;
	}
	return (NULL);
}

int	get_last_char_of_dlr(char *str, t_list *token)
{
	int	i;

	i = -1;
	if (token->key != DQUOTES)
		return (ft_strlen(str));
	while (str[++i] && str[i] != '\''
		&& str[i] != '=' && str[i] != '/' && str[i] != ' ')
		;
	return (i);
}
