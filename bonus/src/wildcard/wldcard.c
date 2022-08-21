/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wldcard.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:59:08 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/11 15:20:12 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void	print_files(t_wldcrd *list)
//{
//	while (list)
//	{
//		printf("%s\n", list->file);
//		list = list->next;
//	}
//}

static t_wldcrd	*new_lst(char *val)
{
	t_wldcrd	*elem;

	elem = (t_wldcrd *) malloc(sizeof(t_wldcrd));
	if (!elem)
		return (0);
	elem->next = NULL;
	elem->file = val;
	return (elem);
}

static t_wldcrd	*wldlast(t_wldcrd *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

static void	wldadd_back(t_wldcrd **lst, t_wldcrd *new)
{
	t_wldcrd	*f;

	if (!(lst && new))
		return ;
	if (*lst)
	{
		f = wldlast(*lst);
		f->next = new;
	}
	else
		*lst = new;
}

static char	*wldcrd2(t_wldcrd *list, DIR *dirp, char *str)
{
	char			*return_value;

	if (!list)
	{
		closedir(dirp);
		return (NULL);
	}
	return_value = select_and_join(list, str);
	closedir(dirp);
	return (return_value);
}

char	*wldcrd(char *str)
{
	t_wldcrd		*list;
	DIR				*dirp;
	struct dirent	*dp;

	list = NULL;
	dirp = opendir(".");
	if (dirp == NULL)
		exit_ms("opendir error!", 1);
	while (1)
	{
		dp = readdir(dirp);
		if (dp == NULL)
			break ;
		if (ft_strncmp(".", dp->d_name, 1) == 0)
			continue ;
		wldadd_back(&list, new_lst(dp->d_name));
	}
	return (wldcrd2(list, dirp, str));
}

//int	main(int argc, char **argv)
//{
//	char	*str;
//
//	(void)argc;
//	str = wldcrd(argv[1]);
//	ft_putendl_fd(str, 1);
//	free(str);
//}
