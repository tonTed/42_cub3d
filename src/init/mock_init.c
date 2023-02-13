#include "../../include/cub3D.h"

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

void	mock_map(t_vars *vars)
{
	vars->m.s.w = 8;
	vars->m.s.h = 8;

	vars->m.m = (int **)malloc(sizeof(int *) * vars->m.s.h);
	int i = 0;
	while (i < vars->m.s.h)
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
	// copy worldMap to vars->m.m
	int x = 0;
	int y = 0;
	while (y < vars->m.s.h)
	{
		x = 0;
		while (x < vars->m.s.w)
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

	// init minimap data
	vars->mm.size.w = 8 * 64;
	vars->mm.size.h = 8 * 64;
	vars->mm.pos.X = 16;
	vars->mm.pos.Y = 16;

	// init map data
	mock_map(vars);


	return (EXIT_SUCCESS);


}