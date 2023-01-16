/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quicksort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 21:23:47 by tonted            #+#    #+#             */
/*   Updated: 2021/12/25 23:04:09 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	divide(int **tab, int start, int end)
{
	int	pivot;
	int	i_pivot;

	pivot = (*tab)[end];
	i_pivot = start;
	while (end > start)
	{
		if ((*tab)[start] < pivot)
		{
			ft_swap(&(*tab)[i_pivot], &(*tab)[start]);
			i_pivot++;
		}
		start++;
	}
	ft_swap(&(*tab)[i_pivot], &(*tab)[end]);
	return (i_pivot);
}

void	quicksort(int **tab, int start, int end)
{
	int	i_pivot;

	if (end > start)
	{
		i_pivot = divide(tab, start, end);
		quicksort(tab, start, i_pivot - 1);
		quicksort(tab, i_pivot + 1, end);
	}
}

/*
int main()
{
	int *tab;
	tab = (int *)malloc(sizeof(int) * 10);
	tab[0] = 30;
	tab[1] = 10;
	tab[2] = 32;
	tab[3] = 4;
	tab[4] = 60;
	tab[5] = 1;
	tab[6] = 82;
	tab[7] = 8;
	tab[8] = 45;
	tab[9] = 50;

	ft_puttabint_fd(tab, 10, 1);
	quicksort(&tab, 0, 9);
	ft_puttabint_fd(tab, 10, 1);

	return 0;
}
*/
