/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabstr_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:56:31 by tonted            #+#    #+#             */
/*   Updated: 2023/03/20 14:24:37 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	add_line_tabstr(char ***tabstr, char *line)
{
	char	**new_tabstr;
	int		i;

	if (!(*tabstr))
	{
		*tabstr = (char **)malloc(sizeof(char *) * 2);
		(*tabstr)[0] = line;
		(*tabstr)[1] = NULL;
		return ;
	}
	new_tabstr = (char **)malloc(sizeof(char *) * (ft_strtablen(*tabstr)
				+ 2));
	i = 0;
	while ((*tabstr)[i])
	{
		new_tabstr[i] = (*tabstr)[i];
		i++;
	}
	new_tabstr[i++] = line;
	new_tabstr[i] = NULL;
	free(*(tabstr));
	*(tabstr) = new_tabstr;
}
