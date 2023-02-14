#include "../include/cub3D.h"

void	free_tab_int_2d(int **tab, int size)
{
	int i = 0;
	while (i < size)
	{
		free_null(tab[i]);
		i++;
	}
	free_null(tab);
}

void	clean_exit(t_vars *vars)
{
	(void)vars;

	free_tab_int_2d(vars->m.m, vars->m.s.h);

	WHOAMI
}