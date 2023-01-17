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

void	hook(void *param)
{
	mlx_t	*mlx;

    mlx = param;
    hook_keyboard(mlx);
	draw_frame(mlx);
}

int32_t init(int ac, char *av[], t_vars *vars)
{
	WHOAMI

	//TODO {END} : change `ac > 2` to `ac != 2` : use a default map for developement
	if (ac > 2)
		return (EXIT_FAILURE);

	// TODO {END} : keep only `if statement inside else`!
	if (ac == 1)
	{
		if (parse_file_map(NULL, vars))
			return (EXIT_FAILURE);
	}
	else
	{
		if (parse_file_map(av[1], vars))
			return (EXIT_FAILURE);
	}

	vars->mlx = mlx_init(WIDTH, HEIGHT, TITLE, false);
	if (!vars->mlx)
		return (EXIT_FAILURE);
	if (init_assets(vars))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}


int32_t	main(int ac, char* av[])
{
	WHOAMI

	t_vars	vars;

    if (init(ac, av, &vars))
        exit(EXIT_FAILURE);

    mlx_loop_hook(vars.mlx, &hook, vars.mlx);

    mlx_loop(vars.mlx);

    mlx_terminate(vars.mlx);
    return (EXIT_SUCCESS);
}