/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 16:48:23 by tonted            #+#    #+#             */
/*   Updated: 2021/12/24 17:05:06 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_isnumber(char *str)
{
	while (ft_iswhitespace(*str))
		str++;
	if (ft_issign(*str))
		str++;
	while (ft_isdigit(*str))
		str++;
	if (*str)
		return (false);
	return (true);
}
