/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 13:07:38 by tonted            #+#    #+#             */
/*   Updated: 2023/01/14 13:12:12 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

#include <memory.h>
#define _WIDTH 3024
#define _HEIGHT 1964

#define WIDTH 1024
#define HEIGHT _HEIGHT * WIDTH / _WIDTH

mlx_image_t	*g_img;

void	hook(void *param)
{
    mlx_t	*mlx;

    mlx = param;
    if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
        mlx_close_window(mlx);
    if (mlx_is_key_down(mlx, MLX_KEY_UP))
        g_img->instances[0].y -= 5;
    if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
        g_img->instances[0].y += 5;
    if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
        g_img->instances[0].x -= 5;
    if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
        g_img->instances[0].x += 5;
}


int32_t	main(void)
{
    mlx_t	*mlx;

    mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
    if (!mlx)
        exit(EXIT_FAILURE);
    g_img = mlx_new_image(mlx, 32, 32);
    memset(g_img->pixels, 255, g_img->width * g_img->height * sizeof(int));
    mlx_image_to_window(mlx, g_img, 0, 0);
    mlx_loop_hook(mlx, &hook, mlx);
    mlx_loop(mlx);
    mlx_terminate(mlx);
    return (EXIT_SUCCESS);
}