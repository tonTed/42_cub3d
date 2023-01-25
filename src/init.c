#include "../include/cub3D.h"

void	mock_init(t_vars *vars)
{

	vars->mmap.bg = mlx_new_image(vars->mlx, WIDTH - 50, HEIGHT - 50);
	int_memset(vars->mmap.bg->pixels, rgba_to_int(100, 100, 100, 255),
			   vars->mmap.bg->width * vars->mmap.bg->height);
	mlx_image_to_window(vars->mlx, vars->mmap.bg, 25, 25);

	vars->player.coord.x = 300;
	vars->player.coord.y = 300;

	vars->mmap.player = mlx_new_image(vars->mlx, 8, 8);
	int_memset(vars->mmap.player->pixels, rgba_to_int(255, 255, 255, 255),
			   vars->mmap.player->width * vars->mmap.player->height);
	mlx_image_to_window(vars->mlx, vars->mmap.player, vars->player.coord.x - 4, vars->player.coord.y - 4);
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

	mock_init(vars);

	return (EXIT_SUCCESS);
}