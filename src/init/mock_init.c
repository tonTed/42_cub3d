#include "../../include/cub3D.h"

void	mock_map(t_vars *vars)
{
	vars->m.s.w = 8;
	vars->m.s.h = 8;

	vars->m.m = (int **)malloc(sizeof(int *) * vars->m.s.h);
	int i = 0;
	while (i < (int)vars->m.s.h)
		vars->m.m[i++] = (int *)malloc(sizeof(int) * vars->m.s.w);

	int worldMap[8][8]=
			{
					{1,1,1,1,1,1,1,1},
					{1,0,1,0,0,0,0,1},
					{1,0,1,0,0,0,0,1},
					{1,0,1,0,0,0,0,1},
					{1,0,0,0,0,0,0,1},
					{1,0,0,0,0,1,0,1},
					{1,0,0,0,0,0,0,1},
					{1,1,1,1,1,1,1,1},
			};
	int x = 0;
	int y = 0;
	while (y < (int)vars->m.s.h)
	{
		x = 0;
		while (x < (int)vars->m.s.w)
		{
			vars->m.m[y][x] = worldMap[y][x];
			x++;
		}
		y++;
	}

}

bool	mock_init(t_vars *vars)
{
	WHOAMI

	// init player data
	vars->p.c.X = 300.0;
	vars->p.c.Y = 300.0;
	vars->p.d.X = 0;
	vars->p.d.Y = -1;
	vars->p.angle = 0.0;

	// init minimap data
	vars->mm.size.w = 8 * 16;
	vars->mm.size.h = 8 * 16;
	vars->mm.pos.X = 16;
	vars->mm.pos.Y = 16;

	// init map data
	mock_map(vars);


	return (EXIT_SUCCESS);


}