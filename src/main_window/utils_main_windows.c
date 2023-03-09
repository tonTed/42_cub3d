/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main_windows.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:40:19 by tonted            #+#    #+#             */
/*   Updated: 2023/03/02 10:44:32 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/**
 * @brief Set the wall height on the screen , the top and bottom of the wall
 * (y position) and the offset of the texture, if the wall is higher than the
 * screen.
 *
 * @param dw		struct of the wall
 * @param height	height of the texture
 *
 */
void	set_wall_height_bottom_top(t_draw_wall *dw, u_int32_t height)
{
	dw->off_y = 0;
	dw->wall_height = (64 * (float) HEIGHT) / dw->ray_length;
	dw->step_y = (double) height / dw->wall_height;
	if (dw->wall_height > (float) HEIGHT)
	{
		dw->off_y = (dw->wall_height - (float) HEIGHT) / 2;
		dw->wall_height = (float) HEIGHT;
		dw->flag = 0x1;
	}
	dw->wall_top = -dw->wall_height / 2 + HEIGHT / 2;
	if (dw->wall_top < 0)
		dw->wall_top = 0;
	dw->wall_bottom = dw->wall_height / 2 + HEIGHT / 2;
	if (dw->wall_bottom >= HEIGHT)
		dw->wall_bottom = HEIGHT - 1;
}

/**
 * @brief Set the x position of the wall on the texture.
 *
 * @param dw		struct of the wall
 * @param vars		main struct of the program
 *
 */
void	set_wall_x_begin(t_draw_wall *dw, t_vars *vars)
{
	if (dw->orientation == NORTH || dw->orientation == SOUTH)
		dw->wall_x = (int)(vars->p.c.X + dw->ray_length_orig
				* cos(dw->ray_angle)) % PIXEL_SIZE;
	else
		dw->wall_x = (int)(vars->p.c.Y + dw->ray_length_orig
				* sin(dw->ray_angle)) % PIXEL_SIZE;
}

/**
 * @brief Set the begin of the texture.
 *
 * @param vars		main struct of the program
 * @param dw		struct of the wall
 *
 */
void	set_begin_vector_texture(t_vars *vars, t_draw_wall *dw)
{
	dw->tex_x = dw->wall_x * vars->a.textures[dw->orientation]->width
		/ PIXEL_SIZE;
	if (dw->orientation == SOUTH || dw->orientation == WEST)
		dw->tex_x = vars->a.textures[dw->orientation]->width - dw->tex_x - 1;
	dw->tex_y = (vars->a.textures[dw->orientation]->height) - dw->off_y
		* dw->step_y;
}
