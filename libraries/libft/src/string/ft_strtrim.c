/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 12:18:50 by tblanco           #+#    #+#             */
/*   Updated: 2021/10/14 09:06:42 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_start_end(char const *s1, char const *set, int step)
{
	int	i;

	i = 0;
	if (step == 1)
		while (ft_ischarinstr(s1[i], set))
			i++;
	if (step == -1)
	{
		i = ft_strlen(s1) - 1;
		while (ft_ischarinstr(s1[i], set) && i >= 0)
			i--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i_start;
	size_t	i_end;
	size_t	len;

	if (!*s1 || !set)
		return (ft_strdup(s1));
	if (ft_issetinstr(s1, set))
		return (ft_strdup(""));
	i_start = ft_get_start_end(s1, set, 1);
	i_end = ft_get_start_end(s1, set, -1);
	len = i_end - i_start + 1;
	return (ft_substr(s1, i_start, len));
}
