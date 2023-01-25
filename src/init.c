#include "../include/cub3D.h"

int32_t init(int ac, char *av[], t_vars *vars)
{
	WHOAMI

	// TODO manage errors messages
	if (ac != 2)
		return (EXIT_FAILURE);
	if (parsing_file_map(av[1], vars))
		return (EXIT_FAILURE);
	vars->mlx = mlx_init(WIDTH, HEIGHT, TITLE, false);
	if (!vars->mlx)
		return (EXIT_FAILURE);
	if (init_assets(vars))
		return (EXIT_FAILURE);
	minimap(vars);

	return (EXIT_SUCCESS);
}