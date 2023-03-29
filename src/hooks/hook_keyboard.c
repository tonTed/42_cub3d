/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_keyboard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 08:24:48 by tblanco           #+#    #+#             */
/*   Updated: 2023/03/20 15:26:31 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (!BONUS)
		return ;
	bonus_manage_collisions(vars, old_pos);
	vars->p.mm_c.X = vars->p.c.X / vars->mm.ratio;
	vars->p.mm_c.Y = vars->p.c.Y / vars->mm.ratio;
}

void	hook_rotation(t_vars *vars)
{
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
	hook_rotation(vars);
}

void	hooks(t_vars *vars)
{

	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	hook_moves(vars);
	if (BONUS)
		bonus_hooks(vars);
}
