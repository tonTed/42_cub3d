#include "../include/cub3D.h"

void	clean_exit(t_vars *vars)
{
	free_null(vars->map.map);
}