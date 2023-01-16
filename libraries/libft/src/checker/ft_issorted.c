/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_issorted.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 22:24:33 by tonted            #+#    #+#             */
/*   Updated: 2021/12/27 11:47:05 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

bool	ft_issorted(int *tab, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len - 1)
	{
		if (tab[i] > tab[i + 1] || tab[len - 1] < tab[len - 2])
			return (false);
		i++;
		len--;
	}
	return (true);
}

/*
int main()
{
	int tab[] = {1, 2, 5, 4};
	printf("%d\n", ft_issorted(tab, 4));
}
*/
