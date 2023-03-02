/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 11:30:03 by tonted            #+#    #+#             */
/*   Updated: 2023/03/02 11:30:41 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	free_tab_int_2d(int **tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free_null(tab[i]);
		i++;
	}
	free_null(tab);
}

void	clean_exit(t_vars *vars)
{
	int	i;

	free_tab_int_2d(vars->m.m, vars->m.s.h);
	i = 0;
	while (i < 4)
	{
		mlx_delete_texture(vars->a.textures[i]);
		vars->a.textures[i] = NULL;
		i++;
	}
	free_null(vars->a.textures);
}
