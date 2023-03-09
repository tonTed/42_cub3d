/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_main_window.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:37:06 by tonted            #+#    #+#             */
/*   Updated: 2023/03/02 10:40:08 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/**
 * @brief Draw ceiling and floor.
 *
 * @param vars			main struct of the program
 * @param start_ceiling	start of the ceiling (y)
 * @param start_floor	start of the floor (y)
 * @param x				x position of the pixel
 *
 */
void static	draw_ceiling_floor_color(t_vars *vars, int start_ceiling,
	int start_floor, int x)
{
	while (start_ceiling >= 0)
		mlx_put_pixel(vars->win, x, start_ceiling--, vars->a.colors[CEILING]);
	while (start_floor < HEIGHT)
		mlx_put_pixel(vars->win, x, start_floor++, vars->a.colors[FLOOR]);
}

/**
 * @brief Manage the fish eye effect.
 *
 * @param vars			main struct of the program
 * @param dw			struct of the wall
 *
 */
void static	fish_eye(t_vars *vars, t_draw_wall *dw)
{
	double	tmp;

	tmp = vars->p.angle - dw->ray_angle;
	if (tmp < 0)
		tmp += 2 * M_PI;
	else if (tmp > 2 * M_PI)
		tmp -= 2 * M_PI;
	dw->ray_length_orig = dw->ray_length;
	dw->ray_length = dw->ray_length * cos(tmp);
}

/**
 * @brief Draw a line vertically on the screen.
 * This function is called for each ray.
 * It will draw the wall, the ceiling and the floor.
 * The wall is drawn by getting the color of the texture at the position
 * of the pixel on the wall.
 * The ceiling and the floor are drawn with the color of the ceiling and
 * the floor.
 *
 * @param vars		main struct of the program.
 * @param dw		struct of the wall.
 * @param x			x position of the pixel.
 *
 */
void static	draw_vertical_line(t_draw_wall *dw, t_vars *vars, int x)
{
	int	tmp_wall_bottom;
	int	color;

	fish_eye(vars, dw);
	set_wall_height_bottom_top(dw, vars->a.textures[dw->orientation]->height);
	set_wall_x_begin(dw, vars);
	tmp_wall_bottom = (int)dw->wall_bottom;
	set_begin_vector_texture(vars, dw);
	while (dw->wall_bottom >= dw->wall_top)
	{
		color = get_pixel_color(vars->a.textures[dw->orientation],
				(int)dw->tex_x, (int)dw->tex_y);
		mlx_put_pixel(vars->win, x, dw->wall_bottom, color);
		dw->tex_y -= dw->step_y;
		dw->wall_bottom--;
	}
	dw->wall_bottom = tmp_wall_bottom;
	if (dw->flag)
		return ;
	draw_ceiling_floor_color(vars, (int)dw->wall_top, (int)dw->wall_bottom, x);
}

/**
 * @brief Draw the main window.
 * This function is called at each frame.
 * It will draw the main window by calling the function draw_vertical_line
 * for each ray.
 * The ray is defined by the player FOV and the width of the window.
 *
 * @param vars		main struct of the program.
 *
 */
void	draw_main_window(t_vars *vars)
{
	t_draw_wall	dw;
	int			i;

	dw.ray_angle = vars->p.angle - vars->p.fov_2;
	dw.step_angle = vars->p.fov / WIDTH;
	i = 0;
	while (i < WIDTH)
	{
		dw.flag = 0x0;
		dw.ray_length = ray_length(&dw, vars);
		mm_draw_rays(vars, &dw, i);
		draw_vertical_line(&dw, vars, i);
		dw.ray_angle += dw.step_angle;
		i++;
	}
}
