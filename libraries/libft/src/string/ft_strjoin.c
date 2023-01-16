/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:08:17 by tblanco           #+#    #+#             */
/*   Updated: 2021/09/23 21:48:55 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	int		len;
	int		i;

	len = ft_strlen(s1) + ft_strlen (s2) + 1;
	ret = malloc(len * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < len && *s1)
		ret[i++] = *s1++;
	while (i < len && *s2)
		ret[i++] = *s2++;
	ret[i] = 0;
	return (ret);
}
