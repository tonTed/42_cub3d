/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:03:15 by tonted            #+#    #+#             */
/*   Updated: 2023/03/02 11:01:59 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"
#define ROT_SPEED 0.05
#define MOVE_SPEED 3
#define POSITIVE 1
#define NEGATIVE 0

/**
 * @brief Function to update the player position
 * 
 * @param vars			Pointer to the struct containing all the variables.
 * @param sign			
 * @param add_to_angle
 *
 */
void	update_player_pos(t_vars *vars, int sign, double add_to_angle)
{
	t_vectorD	old_pos;

	old_pos.X = vars->p.c.X;
	old_pos.Y = vars->p.c.Y;
	if (sign == POSITIVE)
	{
		vars->p.c.X += cos(vars->p.angle + add_to_angle) * MOVE_SPEED;
		vars->p.c.Y += sin(vars->p.angle + add_to_angle) * MOVE_SPEED;
	}
	else
	{
		vars->p.c.X -= cos(vars->p.angle + add_to_angle) * MOVE_SPEED;
		vars->p.c.Y -= sin(vars->p.angle + add_to_angle) * MOVE_SPEED;
	}
	if (BONUS)
		bonus_manage_collisions(vars, old_pos);
	vars->p.mm_c.X = vars->p.c.X / vars->mm.ratio;
	vars->p.mm_c.Y = vars->p.c.Y / vars->mm.ratio;
}

/**
 * @brief Hook moves
 *
 * @param vars	Pointer to the struct containing all the variables.
 *
 */
void	hook_moves(t_vars *vars)
{
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W))
		update_player_pos(vars, POSITIVE, 0);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
		update_player_pos(vars, NEGATIVE, 0);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
		update_player_pos(vars, NEGATIVE, M_PI / 2);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
		update_player_pos(vars, POSITIVE, M_PI / 2);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
	{
		if (vars->p.angle < 0)
			vars->p.angle += 2 * M_PI;
		else
			vars->p.angle -= ROT_SPEED;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
	{
		if (vars->p.angle > 2 * M_PI)
			vars->p.angle -= 2 * M_PI;
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
 * 	- Toggle position minimap (top left, top right, bottom left,
 *		bottom right, remove)
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

void	hooks(t_vars *vars)
{
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	hook_moves(vars);
	hook_configs(vars);
	hook_mouse(vars);
}
