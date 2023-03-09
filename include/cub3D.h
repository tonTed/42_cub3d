/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 13:09:41 by tonted            #+#    #+#             */
/*   Updated: 2023/03/09 14:12:59 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>

# include "../libraries/libft/include/libft.h"
# include "../libraries/MLX42/include/MLX42/MLX42.h"
# include "cub3d_parse.h"
# include "cub3d_configs.h"
# include "cub3d_utils_structs.h"

# ifndef BONUS
#  define BONUS 0
# endif

/**
 * @brief Assets struct
 *
 * @param textures	Textures array
 * @param textures[0]	North texture
 * @param textures[1]	South texture
 * @param textures[2]	West texture
 * @param textures[3]	East texture
 *
 * @param colors	Colors array
 * @param colors[0]	Ceiling color
 * @param colors[1]	Floor color
 *
 */
typedef struct s_assets {
	mlx_texture_t	**textures;
	int 			colors[2];
}	t_assets;

enum e_orientation {
	NORTH,
	SOUTH,
	WEST,
	EAST,
};

enum e_color {
	CEILING,
	FLOOR
};

/**
 * @brief Map configuration struct.
 * [0][0] is on top left and direction is to bottom right.
 *
 * @param m Map[y][x]
 * @param s Map size
 */
typedef struct s_map_config {
	int		**m;
	t_size	s;
}	t_map_config;

/**
 * @brief Player struct
 *
 * @param c Player position
 * @param mm_c Player position on minimap (BONUS)
 * @param angle Player angle
 * @param fov Player field of view
 * @param fov_2 Player field of view / 2
 */
typedef struct s_player {
	t_vectorD	c;
	t_vectorD	mm_c;
	double 		angle;
	double 		fov;
	double 		fov_2;
}	t_player;


/**
 * @brief Mini map struct (BONUS)
 *
 * @param win Mini map window
 * @param pos Mini map position
 * @param size Mini map size
 * @param ratio Mini map ratio
 */
typedef struct s_mini_map {
	mlx_image_t	*win;
	t_vectorI	pos;
	t_size		size;
	int 		ratio;
}	t_mini_map;

/**
 * @brief Map configuration struct
 *
 * @param mlx   mlx structure variables
 * @param win   main win to display (size equals to mlx size)
 * @param p     player structure data
 * @param m     map structure data
 * @param mm    minimap structure data
 * @param a		asset structure data
 */
typedef struct s_vars {
	mlx_t			*mlx;
	mlx_image_t		*win;
	t_player		p;
	t_map_config	m;
	t_mini_map		mm;
    t_assets        a;
	char 			flag;
}	t_vars;

/* hooks */
void    hooks(t_vars *vars);

/* parsing */
bool	parse_file(char *file, t_vars *vars);
bool	parse_textures(t_vars *vars, int fd);
bool	parse_map(t_vars *vars, int fd, char ***buffer);

/* parsing utils */
void	add_line_tabstr(char ***tabstr, char *line);
void	remove_spaces(char **line);

/* initialization */
bool	init(int ac, char *av[], t_vars *vars);
void	init_map(t_vars *vars, char **raw_file);
bool	is_map_closed(t_vars *vars);

/* utils */
void		*int_memset(void *ptr, int value, size_t num);
uint32_t	get_pixel_color(mlx_texture_t *texture, uint32_t x, uint32_t y);
int			gnl(int fd, char **line);

/* utils image */
void	fill_image(mlx_image_t *img, int color);

/* utils draw */
double	ray_length(t_draw_wall *dw, t_vars *vars);

/* draw */
void	draw_main_window(t_vars *vars);
void	draw_minimap(t_vars *vars);
void	draw_bonus(t_vars *vars);

/* utils main windows */
void	set_begin_vector_texture(t_vars *vars, t_draw_wall *dw);
void	set_wall_x_begin(t_draw_wall *dw, t_vars *vars);
void	set_wall_height_bottom_top(t_draw_wall *dw, u_int32_t height);

/* clean / free */
int		clean_textures(t_vars *vars, int ret, char *msg);
int		clean_map(t_vars *vars, int ret, char *msg);
void	clean_exit(t_vars *vars);
void	free_null(void *ptr);

/* bonus */
bool	init_bonus(t_vars *vars);
void	mm_draw_squares(t_vars *vars);
void	mm_draw_rays(t_vars *vars, t_draw_wall *dw, int i);
void	draw_dot(int size, int color, mlx_image_t *win, t_vectorD pos);
void	draw_ray(mlx_image_t *win, t_vectorD pos, double angle, int length);
void	bonus_manage_collisions(t_vars *vars, t_vectorD old_pos);

#endif

/* development */
# define WHOAMI printf(GRN"Function "BMAG"%s"GRN" ran "BGRN"SUCCESSFULLY\n"RESET, __func__);