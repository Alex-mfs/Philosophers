/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_listing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/06 15:42:16 by alfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_ast	*lastpipe(t_ast *lst)
{
	t_ast	*blist;
	t_ast	*ultima;

	blist = lst;
	ultima = NULL;
	while (blist != NULL)
	{
		if (blist && blist->index < 0)
			ultima = blist;
		blist = blist->next;
	}
	if (!ultima)
		return (lst);
	return (ultima);
}

int	cmdlst_size(t_ast *lst, bool total)
{
	int		i;
	t_ast	*blist;

	i = 0;
	blist = lst;
	while (blist != NULL)
	{
		if (total)
			i++;
		else if (blist->index >= 0)
			i++;
		blist = blist->next;
	}
	return (i);
}

t_ast	*cmdlst_penult(t_ast *lst)
{
	t_ast	*penult;

	if (!lst || cmdlst_size(lst, true) < 2)
		return (NULL);
	penult = lst;
	while (penult->next->next != NULL)
		penult = penult->next;
	return (penult);
}

t_ast	*cmdlst_last(t_ast *lst)
{
	t_ast	*ult;

	if (!lst)
		return (NULL);
	ult = lst;
	while (ult->next != NULL)
		ult = ult->next;
	return (ult);
}

void	cmdlst_addback(t_ast **lst, t_ast *new)
{
	t_ast	*ultima;

	if (lst && new)
	{
		if (*lst)
		{
			ultima = cmdlst_last(*lst);
			if (ultima->index < 0)
				new->index = cmdlst_penult(*lst)->index + 1;
			else
				new->index = ultima->index + 1;
			ultima->next = new;
		}
		else
		{
			new->index = 0;
			*lst = new;
		}
	}
}
