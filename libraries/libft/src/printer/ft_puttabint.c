/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puttabint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 21:32:19 by tonted            #+#    #+#             */
/*   Updated: 2022/01/18 21:08:01 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_minintab(int *tab, size_t len)
{
	size_t	i;
	int		min;

	i = 0;
	min = tab[i++];
	while (i < len)
	{
		if (tab[i] < min)
			min = tab[i];
		i++;
	}
	return (min);
}

static int	ft_maxintab(int *tab, size_t len)
{
	size_t	i;
	int		max;

	i = 0;
	max = tab[i++];
	while (i < len)
	{
		if (tab[i] > max)
			max = tab[i];
		i++;
	}
	return (max);
}

void	ft_puttabint_fd(int *tab, size_t len, int fd)
{
	size_t	i;
	int		min;
	int		max;

	if (!len)
		return (ft_putstr_fd(BLU "tab" RESET " -> [empty]\n", fd));
	i = 0;
	min = ft_minintab(tab, len);
	max = ft_maxintab(tab, len);
	ft_putstr_fd(BLU "tab" RESET " -> [", fd);
	while (i < len)
	{
		ft_putstr_fd(MAG "", fd);
		if (tab[i] == min)
			ft_putstr_fd(GRN "", fd);
		else if (tab[i] == max)
			ft_putstr_fd(RED "", fd);
		ft_putnbr_fd(tab[i], fd);
		if (++i < len)
			ft_putstr_fd(RESET ", ", fd);
	}
	ft_putstr_fd(RESET "]\n", fd);
}
