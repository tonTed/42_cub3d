/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_keyboard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:03:15 by tonted            #+#    #+#             */
/*   Updated: 2023/02/17 18:35:32 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"
#define ROT_SPEED 0.05
#define MOVE_SPEED 1
#define POSITIVE 1
#define NEGATIVE 0

void	update_player_pos(t_player *p, int sign, double add_to_angle)
{
	if (sign == POSITIVE)
	{
		p->c.X += cos(p->angle + add_to_angle) * MOVE_SPEED;
		p->c.Y += sin(p->angle + add_to_angle) * MOVE_SPEED;
	}
	else
	{
		p->c.X -= cos(p->angle + add_to_angle) * MOVE_SPEED;
		p->c.Y -= sin(p->angle + add_to_angle) * MOVE_SPEED;
	}
}

void	hook_moves(t_vars *vars)
{
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W))
		update_player_pos(&vars->p, POSITIVE, 0);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
		update_player_pos(&vars->p, NEGATIVE, 0);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
		update_player_pos(&vars->p, NEGATIVE, M_PI / 2);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
		update_player_pos(&vars->p, POSITIVE, M_PI / 2);
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
