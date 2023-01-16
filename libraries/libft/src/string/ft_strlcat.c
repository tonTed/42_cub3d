/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 20:09:12 by tblanco           #+#    #+#             */
/*   Updated: 2021/09/27 14:38:52 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	int		i;

	i = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dst_len > dstsize)
		return (src_len + dstsize);
	else
		src_len += dst_len;
	if (dstsize)
	{
		while (src[i] && (i + dst_len) < dstsize - 1)
		{
			dst[i + dst_len] = src[i];
			i++;
		}
		dst[i + dst_len] = '\0';
	}
	return (src_len);
}
