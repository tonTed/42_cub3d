/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 11:19:44 by tonted            #+#    #+#             */
/*   Updated: 2023/03/02 11:23:08 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// TODO REFACTOR: return in one line
int	get_index_raw(int width_img, t_vectorI pos)
{
	int	len_y;
	int	len_x;
	int	len_line;

	len_line = width_img * 4;
	len_y = len_line * pos.Y;
	len_x = pos.X * 4;
	return (len_y + len_x);
}

/**
 * @brief Draw a dot on the screen.
 * 
 * @param size	size of the dot (should be odd)
 * @param color	color of the dot
 * @param win	pointer to the window
 * @param pos	position of the dot
 */
void	draw_dot(int size, int color, mlx_image_t *win, t_vectorD pos)
{
	int	row;
	int	med;
	int	index;

	med = size / 2;
	row = -med;
	while (row <= med)
	{
		index = get_index_raw(win->width, (t_vectorI){pos.X, pos.Y + row});
		int_memset(&win->pixels[index + (abs(row % size) - med) * 4], color,
			size - abs(row % size) * 2);
		row++;
	}
}
