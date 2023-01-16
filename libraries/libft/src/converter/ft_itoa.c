/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 17:15:14 by tblanco           #+#    #+#             */
/*   Updated: 2021/09/23 21:29:50 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_get_len(long nb)
{
	size_t	len;

	len = 0;
	if (nb < 0)
	{
		len++;
		nb *= -1;
	}
	while (nb >= 10)
	{
		nb /= 10;
		len++;
	}
	return ((size_t)(len + 1));
}

char	*ft_itoa(int nb)
{
	long	nbr;
	int		len;
	char	*ret;

	nbr = nb;
	len = ft_get_len((long)nb);
	ret = (char *)malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	if (nb < 0)
		nbr *= -1;
	ret[len--] = '\0';
	while (len >= 0)
	{
		ret[len--] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (nb < 0)
		ret[0] = '-';
	return (ret);
}
