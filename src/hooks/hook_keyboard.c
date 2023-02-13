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

void    hook_keyboard(t_vars *vars)
{
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(vars->mlx);
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
