/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 00:27:51 by tblanco           #+#    #+#             */
/*   Updated: 2021/09/22 00:32:37 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nb_long;

	nb_long = n;
	if (nb_long < 0)
	{
		ft_putchar_fd('-', fd);
		nb_long = -nb_long;
	}
	if (nb_long > 9)
	{
		ft_putnbr_fd(nb_long / 10, fd);
		ft_putnbr_fd(nb_long % 10, fd);
	}
	else
		ft_putchar_fd(nb_long + '0', fd);
}
