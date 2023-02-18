/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 13:07:38 by tonted            #+#    #+#             */
/*   Updated: 2023/02/17 20:33:41 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

#include <memory.h>

void	hook(void *param)
{
	t_vars 	*vars;

    vars = param;
    hook_keyboard(vars);
	draw_main_window(vars);
	draw_minimap(vars);
	draw_bonus(vars);
}

int32_t	main(int ac, char* av[])
{
	WHOAMI

	t_vars	vars;

    if (init(ac, av, &vars))
        exit(EXIT_FAILURE);

    mlx_loop_hook(vars.mlx, &hook, &vars);

    mlx_loop(vars.mlx);

    mlx_terminate(vars.mlx);
	clean_exit(&vars);
    return (EXIT_SUCCESS);
}