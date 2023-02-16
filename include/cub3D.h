/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 13:09:41 by tonted            #+#    #+#             */
/*   Updated: 2023/02/09 18:34:41 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/libft/include/libft.h"
#include "../libraries/MLX42/include/MLX42/MLX42.h"

#include <stdio.h>
#include <math.h>

#define WIDTH 1024
#define HEIGHT WIDTH / 3 * 2
#define TITLE "cub3d"

/* Colors */
#define REDD 0xFF0000FF
#define GREY 0xFF969696
#define YELLOW 0xFF00FFFF
#define BLACK 0xFF000000
#define WHITE 0xFFFFFFFF
#define ORANGE 0xFF0080FF

typedef struct s_assets {
    mlx_texture_t   *north_texture;
    mlx_texture_t   *south_texture;
    mlx_texture_t	*west_texture;
    mlx_texture_t	*east_texture;
	int             floor;
	int             ceiling;
}	t_assets;

typedef struct s_vectorD {
	double	X;
	double 	Y;
}	t_vectorD;

typedef struct s_vectorI {
	int32_t	X;
	int32_t	Y;
}	t_vectorI;

typedef struct s_size {
	uint16_t	w;
	uint32_t 	h;
}	t_size;

/**
 * @brief Player struct
 *
 * @param c Player position
 * @apram d Player direction
 */
typedef struct s_player {
	t_vectorD	c;
	t_vectorI	d;
	double 		angle;
}	t_player;

/**
 * @brief Mini map struct
 *
 * @param pos Mini map position
 * @param size Mini map size
 */
typedef struct s_mini_map {
	mlx_image_t	*win;
	t_vectorI	pos;
	t_size		size;
}	t_mini_map;

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
}	t_vars;

/* hooks */
void    hook_keyboard(t_vars *vars);

/* parsing_file_map */
bool	parsing_file_map(char *file, t_vars *vars);

/* initialization */
bool	init(int ac, char *av[], t_vars *vars);
bool	init_assets(t_vars *vars);

/* utils */
void	*int_memset(void *ptr, int value, size_t num);
int		rgba_to_int(int r, int g, int b, int a);
void	free_null(void *ptr);
void	clean_exit(t_vars *vars);

/* utils image */
void	fill_image(mlx_image_t *img, int color);

/* utils draw */
void 	draw_walls(t_vars *vars);
void	draw_dot(int size, int color, mlx_image_t *win, t_vectorD pos);
void	draw_ray(mlx_image_t *win, t_vectorD pos, double angle, int length, int color);

/* draw */
void	draw_main_window(t_vars *vars);
void	draw_minimap(t_vars *vars);
void	draw_bonus(t_vars *vars);


/* development */
# define WHOAMI printf(GRN"Function "BMAG"%s"GRN" ran "BGRN"SUCCESSFULLY\n"RESET, __func__);