//
// Created by Teddy BLANCO on 2023-02-13.
//

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

// TODO BONUS: draw a circle
void	draw_dot(int size, int color, mlx_image_t *win, t_vectorD pos)
{
	int row;
	int med;
	int index;

	med = size / 2;
	row = -med;
	while (row <= med)
	{
		index = get_index_raw(win->width, (t_vectorI) {pos.X, pos.Y + row});
		int_memset(&win->pixels[index + (abs(row % size) - med) * 4], color, size - abs(row % size) * 2);
		row++;
	}
}
