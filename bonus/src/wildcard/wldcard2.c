/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wldcard2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:59:08 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/11 15:20:12 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ends_with(char *haystack, char *needle,
int haystack_len, int needle_len)
{
	int	diff_len;

	if (!*needle)
		return (1);
	if (!haystack)
		return (0);
	diff_len = haystack_len - needle_len;
	if (diff_len < 0)
		return (0);
	return (!ft_strncmp(haystack + diff_len, needle, needle_len));
}

static int	selected(char *file, char *wld, int first_iter, char *star_index)
{
	char	*substr;
	char	*strnstr;

	while (*wld)
	{
		star_index = ft_strchr(wld, '*');
		if (star_index == NULL)
			break ;
		if (star_index == wld)
		{
			first_iter = 1;
			++wld;
			continue ;
		}
		substr = ft_substr(wld, 0, star_index - wld);
		if (!substr)
			exit_ms("malloc_rip", 1);
		strnstr = ft_strnstr(file, substr, ft_strlen(file));
		free(substr);
		if (strnstr == NULL || (!first_iter && strnstr != file))
			return (0);
		file = strnstr + (star_index - wld);
		wld = star_index + 1;
	}
	return (ends_with(file, wld, ft_strlen(file), ft_strlen(wld)));
}

static t_wldcrd	*selection(t_wldcrd *list, char *str,
t_wldcrd *bl, t_wldcrd *tmp)
{
	while (list)
	{
		if (!selected(list->file, str, -1, str))
		{
			if (bl == list)
			{
				tmp = list->next;
				bl = list->next;
				free(list);
				list = tmp;
				continue ;
			}
			tmp->next = list->next;
			free(list);
			list = NULL;
			list = tmp->next;
			continue ;
		}
		tmp = list;
		list = list->next;
	}
	return (bl);
}

static char	*join_files(t_wldcrd *list)
{
	char		*finish;
	t_wldcrd	*copy;

	finish = NULL;
	copy = list;
	while (list)
	{
		if (finish)
			strapp(&finish, " ", 1);
		strapp(&finish, list->file, 1);
		list = list->next;
	}
	free_list(copy);
	return (finish);
}

char	*select_and_join(t_wldcrd *list, char *str)
{
	t_wldcrd	*clear_list;

	clear_list = selection(list, str, list, list);
	if (clear_list)
		return (join_files(clear_list));
	return (ft_strdup(""));
}
