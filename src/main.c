/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 13:07:38 by tonted            #+#    #+#             */
/*   Updated: 2023/03/08 10:07:31 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

#include <memory.h>

bool	is_player_on_map(t_vars *vars)
{
	int	x;
	int	y;

	x = (int)vars->p.c.X / PIXEL_SIZE;
	y = (int)vars->p.c.Y / PIXEL_SIZE;
	if (!((x >= 0 && x < (int)vars->m.s.w) && (y >= 0 && y < (int)vars->m.s.h)))
		return (false);
	if (vars->m.m[y][x] != 0)
		return (false);
	return (true);
}

/**
 * @brief Hook function for the main loop.
 *
 * @param param	pointer to the vars struct
 *
 */
void	hook(void *param)
{
	t_vars	*vars;

	vars = param;
	hooks(vars);
	if (is_player_on_map(vars))
	{
		draw_minimap(vars);
		draw_main_window(vars);
		draw_bonus(vars);
	}
}

int32_t	main(int ac, char *av[])
{
	t_vars	vars;

	if (init(ac, av, &vars))
		exit (EXIT_FAILURE);
	mlx_loop_hook(vars.mlx, &hook, &vars);
	mlx_loop(vars.mlx);
	clean_exit(&vars);
	return (EXIT_SUCCESS);
}
