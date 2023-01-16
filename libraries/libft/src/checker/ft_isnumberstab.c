/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumberstab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 17:49:16 by tonted            #+#    #+#             */
/*   Updated: 2021/12/24 17:57:57 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_isnumberstab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (!ft_isnumber(tab[i]))
			return (false);
		i++;
	}
	return (true);
}
