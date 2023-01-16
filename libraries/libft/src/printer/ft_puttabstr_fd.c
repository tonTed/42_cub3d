/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puttabstr_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 19:58:46 by tonted            #+#    #+#             */
/*   Updated: 2021/12/24 14:31:18 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puttabstr_fd(char **tab, int fd)
{
	while (*tab)
	{
		ft_putendl_fd(*tab, fd);
		tab++;
	}
}
