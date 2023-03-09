/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils_structs.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:12:48 by tonted            #+#    #+#             */
/*   Updated: 2023/03/09 14:12:51 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_UTILS_STRUCTS_H
# define CUB3D_UTILS_STRUCTS_H

typedef struct s_vectorD {
	double	X;
	double 	Y;
}	t_vectorD;

typedef struct s_vectorI {
	int32_t	X;
	int32_t	Y;
}	t_vectorI;

typedef struct s_size {
	uint32_t	w;
	uint32_t 	h;
}	t_size;

typedef struct s_draw_wall
{
	double 	wall_height;
	double 	wall_top;
	double 	wall_bottom;
	int 	wall_x;
	double	ray_length;
	double	ray_length_orig;
	double	ray_angle;
	double 	step_angle;
	double	step_y;
	double	off_y;
	int 	tex_x;
	double	tex_y;
	uint8_t orientation;
	char 	flag;
} t_draw_wall;

#endif
