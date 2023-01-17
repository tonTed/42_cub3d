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

#define WIDTH 1024
#define HEIGHT 704
#define TITLE "cub3d"

mlx_image_t	*g_img;

void	hook(void *param)
{
    mlx_t	*mlx;

    mlx = param;
    hook_keyboard(mlx);
}


int32_t	main(void)
{
    mlx_t	*mlx;

    mlx = mlx_init(WIDTH, HEIGHT, TITLE, false);
    if (!mlx)
        exit(EXIT_FAILURE);

    mlx_loop_hook(mlx, &hook, mlx);
    mlx_loop(mlx);

    mlx_terminate(mlx);
    return (EXIT_SUCCESS);
}