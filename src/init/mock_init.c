#include "../../include/cub3D.h"

bool	mock_init(t_vars *vars)
{
	WHOAMI

	// init player data
	vars->p.c.X = 300.0;
	vars->p.c.Y = 300.0;
	vars->p.d.X = 0;
	vars->p.d.Y = -1;

	// init minimap data
	vars->mm.size.w = 8 * 64;
	vars->mm.size.h = 8 * 64;
	vars->mm.pos.X = 16;
	vars->mm.pos.Y = 16;

	return (EXIT_SUCCESS);
}