/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 11:22:51 by tblanco           #+#    #+#             */
/*   Updated: 2021/10/14 08:58:22 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;

	len = ft_lower(len, ft_strlen(&s[start])) + 1;
	ret = malloc(len * sizeof(char));
	if (!ret)
		return (NULL);
	if (ft_strlen(s) < start)
		ret[0] = 0;
	else
		ft_strlcpy(ret, &s[start], len);
	return (ret);
}
