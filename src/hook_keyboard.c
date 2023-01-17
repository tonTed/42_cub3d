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

#include "../include/cub3D.h"

void    hook_keyboard(mlx_t *mlx)
{
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
        mlx_close_window(mlx);
    if (mlx_is_key_down(mlx, MLX_KEY_W))
        printf("Move Forward\n");
    if (mlx_is_key_down(mlx, MLX_KEY_S))
        printf("Move Back\n");
    if (mlx_is_key_down(mlx, MLX_KEY_A))
        printf("Strafe Left\n");
    if (mlx_is_key_down(mlx, MLX_KEY_D))
        printf("Strafe Right\n");
    if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
        printf("Rotate Left\n");
    if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
        printf("Rotate Right\n");
}