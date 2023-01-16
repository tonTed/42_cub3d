/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 11:14:17 by tblanco           #+#    #+#             */
/*   Updated: 2021/09/27 18:37:42 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*c_dst;
	const char	*c_src = src;

	if (!dst && !src)
		return (NULL);
	c_dst = dst;
	if (c_dst < c_src)
		while (len--)
			*c_dst++ = *c_src++;
	else
		while (len--)
			c_dst[len] = c_src[len];
	return (dst);
}
