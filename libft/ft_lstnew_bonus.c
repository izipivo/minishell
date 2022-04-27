/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:37:50 by sdonny            #+#    #+#             */
/*   Updated: 2022/04/27 16:41:44 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char key, char val, char in_q)
{
	t_list	*elem;

	elem = (t_list *) malloc(sizeof(t_list));
	if (!elem)
		return (0);
	elem->next = NULL;
	elem->key = key;
	elem->val = val;
	elem->in_q = in_q;
	return (elem);
}
