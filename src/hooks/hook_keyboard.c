/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_keyboard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:03:15 by tonted            #+#    #+#             */
/*   Updated: 2023/01/17 11:03:17 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void    hook_keyboard(t_vars *vars)
{
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(vars->mlx);
    if (mlx_is_key_down(vars->mlx, MLX_KEY_W))
	{
		vars->player.coord.y -= vars->player.delta.y;
		vars->player.coord.x -= vars->player.delta.x;
		vars->mmap.player->instances[0].y -= 5;
        printf("Move Forward\n");
	}
    if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
	{
		vars->player.coord.y += vars->player.delta.y;
		vars->player.coord.x += vars->player.delta.x;
		vars->mmap.player->instances[0].y += 5;
        printf("Move Back\n");
	}
    if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
	{
		vars->player.coord.x -= 5;
		vars->mmap.player->instances[0].x -= 5;
        printf("Strafe Left\n");
	}
    if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
	{
		vars->player.coord.x += 5;
		vars->mmap.player->instances[0].x += 5;
        printf("Strafe Right\n");
	}
    if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
	{
        vars->player.angle -= 0.1;
		if (vars->player.angle < 0)
			vars->player.angle += 2 * PI;
		vars->player.delta.x = cos(vars->player.angle);
		vars->player.delta.y = sin(vars->player.angle);
		printf("Rotate Left\n");
	}
    if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
	{
        vars->player.angle += 0.1;
		if (vars->player.angle > 2 * PI)
			vars->player.angle -= 2 * PI;
		vars->player.delta.x = cos(vars->player.angle);
		vars->player.delta.y = sin(vars->player.angle);
        printf("Rotate Right\n");
	}
}
