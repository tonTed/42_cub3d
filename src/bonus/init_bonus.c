//
// Created by Teddy BLANCO on 2023-03-09.
//

#include "../../include/cub3D.h"

static void	init_bonus_data(t_vars *vars)
{
	vars->mm.size.w = vars->m.s.w * MM_PIXEL_SIZE;
	vars->mm.size.h = vars->m.s.h * MM_PIXEL_SIZE;
	vars->mm.pos.X = 16;
	vars->mm.pos.Y = 16;
	vars->mm.ratio = PIXEL_SIZE / MM_PIXEL_SIZE;
	vars->p.mm_c.X = vars->p.c.X / vars->mm.ratio;
	vars->p.mm_c.Y = vars->p.c.Y / vars->mm.ratio;
}

static int	init_bonus_windows(t_vars *vars)
{
	vars->mm.win = mlx_new_image(vars->mlx, vars->mm.size.w, vars->mm.size.h);
	if (!vars->mm.win)
	{
		mlx_delete_image(vars->mlx, vars->win);
		return (clean_map(vars, EXIT_FAILURE, "Error: mlx_new_image failed.\n"));
	}
	mlx_image_to_window(vars->mlx, vars->mm.win, vars->mm.pos.X,
						vars->mm.pos.Y);
	return (EXIT_SUCCESS);
}

bool	init_bonus(t_vars *vars)
{
	if (!BONUS)
		return (EXIT_SUCCESS);
	init_bonus_data(vars);
	if (init_bonus_windows(vars))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}