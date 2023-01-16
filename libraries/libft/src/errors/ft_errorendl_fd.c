/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errorendl_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 18:37:40 by tonted            #+#    #+#             */
/*   Updated: 2021/12/27 13:46:59 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_errormess_fd(int fd, char *message)
{
	ft_putstr_fd(BRED, fd);
	ft_putstr_fd(message, fd);
	ft_putstr_fd(RESET, fd);
}
