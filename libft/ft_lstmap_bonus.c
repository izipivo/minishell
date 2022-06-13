/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:37:50 by sdonny            #+#    #+#             */
/*   Updated: 2022/05/01 14:58:54 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(char	*), void (*del)(char *))
{
	t_list	*elem;
	t_list	*bl;	

	bl = 0;
	if (!(lst && f && del))
		return (0);
	while (lst)
	{
		elem = ft_lstnew(lst->key, f(lst->val));
		if (elem)
			ft_lstadd_back(&bl, elem);
		else
		{
			ft_lstclear(&bl, del);
			lst = 0;
			return (0);
		}
		lst = lst->next;
	}
	return (bl);
}
