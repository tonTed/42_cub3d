/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_keyboard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:03:15 by tonted            #+#    #+#             */
/*   Updated: 2023/02/09 18:48:22 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"
#define ROT_SPEED 0.05
#define MOVE_SPEED 1

void	hook_moves(t_vars *vars)
{
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W))
	{
		vars->p.c.X += cos(vars->p.angle) * MOVE_SPEED;
		vars->p.c.Y += sin(vars->p.angle) * MOVE_SPEED;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
	{
		vars->p.c.X -= cos(vars->p.angle) * MOVE_SPEED;
		vars->p.c.Y -= sin(vars->p.angle) * MOVE_SPEED;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
	{
		vars->p.c.X -= cos(vars->p.angle + M_PI / 2) * MOVE_SPEED;
		vars->p.c.Y -= sin(vars->p.angle + M_PI / 2) * MOVE_SPEED;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
	{
		vars->p.c.X += cos(vars->p.angle + M_PI / 2) * MOVE_SPEED;
		vars->p.c.Y += sin(vars->p.angle + M_PI / 2) * MOVE_SPEED;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
	{
		if (vars->p.angle < 0)
			vars->p.angle = 2 * M_PI;
		else
			vars->p.angle -= ROT_SPEED;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
	{
		if (vars->p.angle > 2 * M_PI)
			vars->p.angle = 0;
		else
			vars->p.angle += ROT_SPEED;
	}
}

/**
 * @brief Hook configs
 *
 * @param vars
 *
 * TODO BONUS: Add config hook
 * 	- Toggle minimap/map
 * 	- Toggle position minimap (top left, top right, bottom left, bottom right, remove)
 */
void	hook_configs(t_vars *vars)
{
	if (mlx_is_key_down(vars->mlx, MLX_KEY_M))
	{
		printf("Toggle Minimap/Map\n");
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_P))
	{
		printf("Toggle position minimap\n");
	}
}

/**
 * @brief Hook mouse
 *
 * @param vars
 *
 * TODO BONUS: Add mouse hook
 * 	- Mouse cursor position rotation lateral
 * 	- Mouse click to shoot, launch sprite
 */
void	hook_mouse(t_vars *vars)
{
	(void)vars;
}

void    hook_keyboard(t_vars *vars)
{
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(vars->mlx);
	hook_moves(vars);
	hook_configs(vars);
	hook_mouse(vars);
}
