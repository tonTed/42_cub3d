
#include "../../include/cub3D.h"

#define squareSize 16
#define SHIFT 1

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


/**
 * @brief Draw a ray from a position with a given angle and length
 *
 * @param color		Color of the ray
 * @param win		Window to draw on
 * @param pos		Position of the start ray
 * @param angle		Angle of the ray
 * @param length	Length of the ray
 *
 * TODO: remove one parameter
 */
void	draw_ray(mlx_image_t *win, t_vectorD pos, double angle, int length, int color)
{
	t_vectorD	coord;
	t_vectorD	inc;
	int			i;

	inc.X = cos(angle);
	inc.Y = sin(angle);
	coord.X = pos.X;
	coord.Y = pos.Y;
	i = 0;
	while (i < length)
	{
		mlx_put_pixel(win, coord.X, coord.Y, color);
		coord.X += inc.X;
		coord.Y += inc.Y;
		i++;
	}
}

void	mm_draw_player(t_vars *vars)
{
	t_vectorD sa_mere;

	sa_mere.X = vars->p.c.X/4;
	sa_mere.Y = vars->p.c.Y/4;
	draw_dot(9, ORANGE, vars->mm.win, sa_mere);
	draw_ray(vars->mm.win, sa_mere, vars->p.angle, 16, 0xFF0000FF);

}

void	draw_minimap(t_vars *vars)
{
	fill_image(vars->mm.win, GREY);
	mm_draw_squares(vars);
	mm_draw_player(vars);
}