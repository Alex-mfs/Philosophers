/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2023/07/30 23:01:12 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*destlist;
	t_list	*dest;
	void	*cont;

	destlist = 0;
	if (lst && f && del)
	{
		while (lst)
		{
			cont = f(lst->content);
			dest = ft_lstnew(cont);
			if (!dest)
			{
				del(cont);
				ft_lstclear(&destlist, del);
				return (NULL);
			}
			ft_lstadd_back(&destlist, dest);
			lst = lst->next;
		}
	}
	return (destlist);
}
