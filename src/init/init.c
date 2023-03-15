/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:58:13 by tonted            #+#    #+#             */
/*   Updated: 2023/03/02 10:58:43 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static bool	init_textures(t_vars *vars)
{
	vars->a.textures = (mlx_texture_t **)malloc(sizeof(mlx_texture_t *) * 4);
	if (vars->a.textures == NULL)
	{
		printf("Error: Malloc failed [%s].\n", __func__);
		return (false);
	}
	vars->a.textures[NORTH] = NULL;
	vars->a.textures[SOUTH] = NULL;
	vars->a.textures[WEST] = NULL;
	vars->a.textures[EAST] = NULL;
	return (true);
}

/**
 * @brief check if the arguments are valid and call the right function for
 * initialize the project.
 *
 * @param ac	arguments count
 * @param av	arguments values (av[1] is the .cube file)
 * @param vars	global variables
 *
 * @return EXIT_SUCCESS if all is ok
 * @return EXIT_FAILURE if an error occurred
 *
 */
bool	check_args(int ac, char *av[], t_vars *vars)
{
	if (ac != 2)
	{
		printf("Error: Wrong number of arguments.\n");
		return (EXIT_FAILURE);
	}
	if (!init_textures(vars))
		return (EXIT_FAILURE);
	return (parse_file(av[1], vars));
}

/**
 * @brief initialize main window and minimap window and display them.
 *
 * @param vars	global variables
 *
 * @return EXIT_SUCCESS if all is ok, EXIT_FAILURE if an error occurred.
 *
 */
#define JUMP_HEIGHT 64
bool	init_win_images(t_vars *vars)
{
	vars->win = mlx_new_image(vars->mlx, WIDTH, HEIGHT + JUMP_HEIGHT);
	if (!vars->win)
		return (clean_map(vars, EXIT_FAILURE, "Error: mlx_new_image failed.\n"));
	mlx_image_to_window(vars->mlx, vars->win, 0, 0);
	return (EXIT_SUCCESS);
}

/**
 * @brief initialize mlx
 *
 * @param vars	global variables
 *
 * @return EXIT_SUCCESS if all is ok, EXIT_FAILURE if an error occurred.
 *
 */
bool	init_mlx(t_vars *vars)
{
	vars->mlx = mlx_init(WIDTH, HEIGHT, TITLE, false);
	if (!vars->mlx)
		return (clean_map(vars, EXIT_FAILURE, "Error: mlx_init failed.\n"));
	return (EXIT_SUCCESS);
}

/**
 * @brief init all project
 *
 * @param vars	global variables
 *
 * @return EXIT_SUCCESS if all is ok
 * @return EXIT_FAILURE if an error occurred
 *
 */
bool	init(int ac, char *av[], t_vars *vars)
{
	vars->flag = 0x0;
	vars->m.s.h = 0;
	vars->m.s.w = 0;
	if (check_args(ac, av, vars))
		return (EXIT_FAILURE);
	if (init_mlx(vars))
		return (EXIT_FAILURE);
	if (init_win_images(vars))
		return (EXIT_FAILURE);
	if (init_bonus(vars))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
