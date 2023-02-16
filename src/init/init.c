#include "../../include/cub3D.h"

// TODO remove this function in production.
bool	mock_init(t_vars *vars);

/**
 * @brief check if the arguments are valid and call the right function for initialize the project.
 *
 * @param ac	arguments count
 * @param av	arguments values (av[1] is the .cube file)
 * @param vars	global variables
 *
 * @return EXIT_SUCCESS if all is ok
 * @return EXIT_FAILURE if an error occurred
 *
 * TODO: manage errors messages: replace all EXIT_FAILURE by function that print error message and return EXIT_FAILURE.
 */
bool	check_args(int ac, char *av[], t_vars *vars)
{
	if (ac != 2)
		return (EXIT_FAILURE);
	if (!ft_strncmp(av[1], "-d", ft_strlen(av[1])))
		return (mock_init(vars));
	else
		return (parsing_file_map(av[2], vars));
}

/**
 * @brief initialize main window and minimap window and display them.
 *
 * @param vars	global variables
 *
 * @return EXIT_SUCCESS if all is ok, EXIT_FAILURE if an error occurred.
 *
 */
bool	init_win_images(t_vars *vars)
{
	vars->win = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (!vars->win)
		return (EXIT_FAILURE);

	vars->mm.win = mlx_new_image(vars->mlx, vars->mm.size.w, vars->mm.size.h);
	if (!vars->mm.win)
		return (EXIT_FAILURE);

	mlx_image_to_window(vars->mlx, vars->win, 0, 0);
	mlx_image_to_window(vars->mlx, vars->mm.win, vars->mm.pos.X, vars->mm.pos.Y);

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
		return (EXIT_FAILURE);
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
 * TODO: manage errors messages: replace all EXIT_FAILURE by function that print error message and return EXIT_FAILURE.
 */
bool init(int ac, char *av[], t_vars *vars)
{
	if (check_args(ac, av, vars))
		return (EXIT_FAILURE);
	if (init_mlx(vars))
		return (EXIT_FAILURE);
	if (init_win_images(vars))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}