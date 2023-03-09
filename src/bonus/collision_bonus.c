/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:51:29 by tonted            #+#    #+#             */
/*   Updated: 2023/03/09 14:51:30 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	bonus_manage_collisions(t_vars *vars, t_vectorD old_pos)
{
	if (vars->m.m[(int)vars->p.c.Y / 64][(int)vars->p.c.X / 64] == 1)
	{
		vars->p.c.X = old_pos.X;
		vars->p.c.Y = old_pos.Y;
	}
}
