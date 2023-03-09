/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:14:00 by tonted            #+#    #+#             */
/*   Updated: 2023/03/09 14:15:15 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	init_bonus_data(t_vars *v)
{
	v->mm.size.w = v->m.s.w * MM_PIXEL_SIZE;
	v->mm.size.h = v->m.s.h * MM_PIXEL_SIZE;
	v->mm.pos.X = 16;
	v->mm.pos.Y = 16;
	v->mm.ratio = PIXEL_SIZE / MM_PIXEL_SIZE;
	v->p.mm_c.X = v->p.c.X / v->mm.ratio;
	v->p.mm_c.Y = v->p.c.Y / v->mm.ratio;
}

static int	init_bonus_windows(t_vars *v)
{
	v->mm.win = mlx_new_image(v->mlx, v->mm.size.w, v->mm.size.h);
	if (!v->mm.win)
	{
		mlx_delete_image(v->mlx, v->win);
		return (clean_map(v, EXIT_FAILURE, "Error: mlx_new_image failed.\n"));
	}
	mlx_image_to_window(v->mlx, v->mm.win, v->mm.pos.X, v->mm.pos.Y);
	return (EXIT_SUCCESS);
}

bool	init_bonus(t_vars *v)
{
	if (!BONUS)
		return (EXIT_SUCCESS);
	init_bonus_data(v);
	if (init_bonus_windows(v))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
