/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 11:03:58 by tblanco           #+#    #+#             */
/*   Updated: 2021/10/14 09:00:59 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*tab;

	if (!count || !size)
	{
		count = 1;
		size = 1;
	}
	tab = malloc((count) * (sizeof(char) * size));
	if (!tab)
		return (NULL);
	ft_bzero(tab, count * size);
	return ((void *)tab);
}
