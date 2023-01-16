/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 22:38:09 by tblanco           #+#    #+#             */
/*   Updated: 2021/09/27 18:27:27 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Itère sur la liste lst et applique la fonction f au contenu de chaque
**	élément. Crée une nouvelle liste résultant des applications successives de
**	f. la fonction del est la pour detruire le contenu d un element si
**	necessaire
*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*begin;
	t_list	*cur;

	if (lst && f)
	{
		begin = ft_lstnew(f(lst->content));
		cur = begin;
		while (lst->next)
		{
			lst = lst->next;
			cur->next = ft_lstnew(f(lst->content));
			if (!cur->next)
			{
				ft_lstclear(&begin, del);
				return (NULL);
			}
			cur = cur->next;
		}
		return (begin);
	}
	return (NULL);
}
