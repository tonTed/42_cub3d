/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:05:35 by tonted            #+#    #+#             */
/*   Updated: 2023/03/08 10:05:42 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	print_map(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < (int)vars->m.s.h)
	{
		j = 0;
		while (j < (int)vars->m.s.w)
		{
			printf("[%d]", vars->m.m[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	allocate_map_array(t_vars *vars, char **raw_file)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	y = 0;
	vars->m.m = (int **)ft_calloc(1, sizeof(int *) * vars->m.s.h);
	while (i < (int)vars->m.s.h)
		vars->m.m[i++] = (int *)ft_calloc(1, sizeof(int) * vars->m.s.w);
	while (y < (int)vars->m.s.h)
	{
		x = 0;
		while (x < (int)vars->m.s.w && raw_file[y][x])
		{
			vars->m.m[y][x] = raw_file[y][x] - '0';
			x++;
		}
		while (x < (int)vars->m.s.w)
			vars->m.m[y][x++] = -16;
		y++;
	}
}

void	init_map(t_vars *vars, char **raw_file)
{
	vars->m.s.h++;
	allocate_map_array(vars, raw_file);
	vars->p.fov = FOV;
	vars->p.fov_2 = vars->p.fov / 2.0;
}
