/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_background.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 11:15:56 by tonted            #+#    #+#             */
/*   Updated: 2023/03/02 11:18:22 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/**
 * @brief Get the index of the pixel in the array of pixels.
 *
 * @param vars	pointer to main struct of the program
 * @param pos	position of the square
 *
 */
int static	mm_get_index(int width_img, t_vectorI pos, int row)
{
	int	len_y;
	int	len_x;
	int	len_line;
	int	len_line_square;
	int	len_line_squares;

	len_line = width_img * 4;
	len_line_square = MM_PIXEL_SIZE * 4;
	len_line_squares = len_line * MM_PIXEL_SIZE;
	len_y = len_line_squares * pos.Y;
	len_x = (pos.X * len_line_square) + (len_line * row);
	return (len_y + len_x);
}

/**
 * @brief Draw a square on the minimap.
 *
 * @param vars	pointer to main struct of the program
 * @param pos	position of the square
 *
 */
void static	mm_draw_square(t_vars *vars, t_vectorI pos)
{
	int	row;
	int	index;

	row = SHIFT;
	while (row < MM_PIXEL_SIZE - SHIFT)
	{
		index = mm_get_index(vars->mm.win->width, pos, row);
		if (vars->m.m[pos.Y][pos.X] == 1)
			int_memset(&vars->mm.win->pixels[index + SHIFT * 4], 0xFF000000,
				MM_PIXEL_SIZE - SHIFT * 2);
		else
			int_memset(&vars->mm.win->pixels[index + SHIFT * 4], 0xFFFFFFFF,
				MM_PIXEL_SIZE - SHIFT * 2);
		row++;
	}
}

/**
 * @brief Draw all the squares on the minimap.
 *
 * @param vars	pointer to main struct of the program
 *
 */
void	mm_draw_squares(t_vars *vars)
{
	t_vectorI	coord;

	coord.Y = 0;
	while (coord.Y < (int)vars->m.s.h)
	{
		coord.X = 0;
		while (coord.X < (int)vars->m.s.w)
		{
			mm_draw_square(vars, coord);
			coord.X++;
		}
		coord.Y++;
	}
}
