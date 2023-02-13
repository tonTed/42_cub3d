
#include "../../include/cub3D.h"

#define squareSize 64
#define SHIFT 1

#define BLACK 0xFF000000
#define WHITE 0xFFFFFFFF

int	mm_get_index(int width_img, t_vectorI pos, int row)
{
	int	len_y;
	int	len_x;

	int	len_line = width_img * 4;
	int len_line_square = squareSize * 4;
	int len_line_squares = len_line * squareSize;

	len_y = len_line_squares * pos.Y;
	len_x = (pos.X * len_line_square) + (len_line * row);

	return (len_y + len_x);
}


void	mm_draw_square(t_vars *vars, t_vectorI pos)
{
	int row;
	int index;

	row = SHIFT;
	while (row < squareSize - SHIFT)
	{
		index = mm_get_index(vars->mm.win->width, pos, row);
		if (vars->m.m[pos.Y][pos.X] == 1)
			int_memset(&vars->mm.win->pixels[index + SHIFT * 4], BLACK, squareSize - SHIFT * 2);
		else
			int_memset(&vars->mm.win->pixels[index + SHIFT * 4], WHITE, squareSize - SHIFT * 2);
		row++;
	}
}

void	mm_draw_squares(t_vars *vars)
{
	t_vectorI	coord;

	coord.Y = 0;
	while (coord.Y < vars->m.s.h)
	{
		coord.X = 0;
		while (coord.X < vars->m.s.w)
		{
			mm_draw_square(vars, coord);
			coord.X++;
		}
		coord.Y++;
	}
}

void	draw_minimap(t_vars *vars)
{
	fill_image(vars->mm.win, GREY);
	mm_draw_squares(vars);
}