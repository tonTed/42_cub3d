/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 10:35:56 by tblanco           #+#    #+#             */
/*   Updated: 2021/09/23 21:30:57 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*c_s;

	c_s = (unsigned char *)s;
	while (n--)
	{
		if (*c_s != (unsigned char)c)
			c_s++;
		else
			return (c_s);
	}
	return (NULL);
}
