/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumberzero.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 23:12:23 by tonted            #+#    #+#             */
/*   Updated: 2021/12/25 23:12:39 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	isnumberzero(char *str)
{
	while (ft_iswhitespace(*str))
		str++;
	if (ft_issign(*str))
		str++;
	while (*str == '0')
		str++;
	if (*str)
		return (false);
	return (true);
}
