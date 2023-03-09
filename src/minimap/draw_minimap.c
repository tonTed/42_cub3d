/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 11:04:03 by tonted            #+#    #+#             */
/*   Updated: 2023/03/02 11:17:58 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/**
 * @brief Draw rays on the minimap.
 *
 * @param vars	pointer to main struct of the program
 * @param dw	pointer to a struct to data needed to draw walls
 * @param i		index of the ray
 *
 *
 */
void	mm_draw_rays(t_vars *vars, t_draw_wall *dw, int i)
{
	if (i % 64 != 0)
		return ;
	draw_ray(vars->mm.win, vars->p.mm_c, dw->ray_angle, dw->ray_length
		/ vars->mm.ratio);
}

/**
 * @brief Draw a ray from a position with a given ray_angle and length
 *
 * @param color		Color of the ray
 * @param win		Window to draw on
 * @param pos		Position of the start ray
 * @param angle		Angle of the ray
 * @param length	Length of the ray
 *
 */
void	draw_ray(mlx_image_t *win, t_vectorD pos, double angle, int length)
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
		mlx_put_pixel(win, coord.X, coord.Y, RAY_COLOR);
		coord.X += inc.X;
		coord.Y += inc.Y;
		i++;
	}
}

/**
 * @brief Draw the player on the minimap.
 *
 * @param vars	pointer to main struct of the program
 *
 */
void	mm_draw_player(t_vars *vars)
{
	draw_dot(DOT_PLAYER_SIZE, DOT_PLAYER_COLOR,
		vars->mm.win, vars->p.mm_c);
	draw_ray(vars->mm.win, vars->p.mm_c, vars->p.angle, RAY_LENGTH);
}

/**
 * @brief Draw the minimap.
 *
 * @param vars	pointer to main struct of the program
 *
 */
void	draw_minimap(t_vars *vars)
{
	fill_image(vars->mm.win, 0xFF808080);
	mm_draw_squares(vars);
	mm_draw_player(vars);
}
