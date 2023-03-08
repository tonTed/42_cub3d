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

void	get_map_size(t_vars *vars, char **raw_file)
{
	int	i;
	int	j;

	i = 0;
	vars->m.s.h = 0;
	vars->m.s.w = 0;
	while (raw_file[i])
	{
		j = ft_strlen(raw_file[i]);
		if ((int)vars->m.s.w < j)
			vars->m.s.w = j;
		i ++;
	}
	vars->m.s.h = i;
}

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
	print_map(vars);
}

void	init_map(t_vars *vars, char **raw_file)
{
	get_map_size(vars, raw_file);
	allocate_map_array(vars, raw_file);
	vars->mm.size.w = vars->m.s.w * MM_PIXEL_SIZE;
	vars->mm.size.h = vars->m.s.h * MM_PIXEL_SIZE;
	vars->mm.pos.X = 16;
	vars->mm.pos.Y = 16;
	vars->mm.ratio = PIXEL_SIZE / MM_PIXEL_SIZE;
	vars->p.mm_c.X = vars->p.c.X / vars->mm.ratio;
	vars->p.mm_c.Y = vars->p.c.Y / vars->mm.ratio;
	vars->p.fov = FOV;
	vars->p.fov_2 = vars->p.fov / 2.0;
}
