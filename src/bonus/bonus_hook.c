/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:12:18 by tonted            #+#    #+#             */
/*   Updated: 2023/03/09 15:12:22 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

#define MOUSE_SPEED 0.04

/**
 * @brief Hook configs
 *
 * @param vars
 *
 * TODO BONUS: Add config hook
 * 	- Toggle minimap/map
 * 	- Toggle position minimap (top left, top right, bottom left,
 *		bottom right, remove)
 */
static void	hook_configs(t_vars *vars)
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
 * 	- Mouse cursor position rotation lateral (works with mouse click)
 * 	- Mouse click to shoot, launch sprite
 */
static void	hook_mouse(t_vars *vars)
{
	static t_vectorD	mouse_pos = {WIDTH / 2, HEIGHT / 2};
	t_vectorI			new_mouse_pos;

	mlx_get_mouse_pos(vars->mlx, &new_mouse_pos.X, &new_mouse_pos.Y);
	if (new_mouse_pos.X != mouse_pos.X && mlx_is_mouse_down(vars->mlx, 1))
	{
		if (new_mouse_pos.X > mouse_pos.X)
			vars->p.angle += MOUSE_SPEED;
		else
			vars->p.angle -= MOUSE_SPEED;
	}
	mouse_pos.X = new_mouse_pos.X;
	mouse_pos.Y = new_mouse_pos.Y;
}

void	bonus_hooks(t_vars *vars)
{
	hook_configs(vars);
	hook_mouse(vars);
}
