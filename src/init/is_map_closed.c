/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_closed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:05:49 by tonted            #+#    #+#             */
/*   Updated: 2023/03/08 10:05:51 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static bool	is_first_last_row_closed(t_vars *vars)
{
	u_int32_t	i;

	i = 0;
	while (i < vars->m.s.w)
	{
		if (vars->m.m[0][i] != 1 && vars->m.m[0][i] != -16)
			return (false);
		if (vars->m.m[vars->m.s.h - 1][i] != 1
			&& vars->m.m[vars->m.s.h - 1][i] != -16)
			return (false);
		i++;
	}
	return (true);
}

static bool	is_first_last_column_closed(t_vars *vars)
{
	u_int32_t	i;

	i = 0;
	while (i < vars->m.s.h)
	{
		if (vars->m.m[i][0] != 1 && vars->m.m[i][0] != -16)
			return (false);
		if (vars->m.m[i][vars->m.s.w - 1] != 1
			&& vars->m.m[i][vars->m.s.w - 1] != -16)
			return (false);
		i++;
	}
	return (true);
}

static bool	is_not_zero_surrounded_by_spaces(t_vars *vars)
{
	u_int32_t	i;
	u_int32_t	j;

	i = 1;
	while (i < vars->m.s.h - 1)
	{
		j = 1;
		while (j < vars->m.s.w - 1)
		{
			if (vars->m.m[i][j] == 0)
			{
				if ((vars->m.m[i - 1][j] == -16 || vars->m.m[i + 1][j] == -16)
					|| (vars->m.m[i][j - 1] == -16
					|| vars->m.m[i][j + 1] == -16))
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

bool	is_map_closed(t_vars *vars)
{
	if (!is_first_last_row_closed(vars))
		return (false);
	if (!is_first_last_column_closed(vars))
		return (false);
	if (!is_not_zero_surrounded_by_spaces(vars))
		return (false);
	return (true);
}
