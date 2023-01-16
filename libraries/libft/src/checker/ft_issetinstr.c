/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_issetinstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 09:06:52 by tblanco           #+#    #+#             */
/*   Updated: 2021/10/14 09:07:10 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_issetinstr(char const *s, char const *set)
{
	while (*s)
		if (!(ft_ischarinstr(*s++, set)))
			return (0);
	return (1);
}
