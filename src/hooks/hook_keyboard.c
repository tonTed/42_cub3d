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

void	hook_moves(t_vars *vars)
{
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W))
	{
		printf("Move Forward\n");
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
	{
		printf("Move Back\n");
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
	{
		printf("Strafe Left\n");
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
	{
		printf("Strafe Right\n");
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
	{
		printf("Rotate Left\n");
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
	{
		printf("Rotate Right\n");
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
