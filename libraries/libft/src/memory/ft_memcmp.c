/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 10:26:24 by tblanco           #+#    #+#             */
/*   Updated: 2021/09/23 21:47:51 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*c_s1 = s1;
	const unsigned char	*c_s2 = s2;

	while (n--)
	{
		if (*c_s1 != *c_s2)
			return (*c_s1 - *c_s2);
		else
		{
			c_s1++;
			c_s2++;
		}
	}
	return (0);
}
