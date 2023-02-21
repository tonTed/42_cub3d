/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 13:09:41 by tonted            #+#    #+#             */
/*   Updated: 2023/02/18 11:08:17 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/libft/include/libft.h"
#include "../libraries/MLX42/include/MLX42/MLX42.h"

#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

/* GENERAL CONFIGS */
#define WIDTH 1024
#define HEIGHT 688
#define TITLE "cub3d"

/* Colors */
#define WHITEH 0xFFFFFFFF
#define BLACKH 0x000000FF
#define GREYH 0x808080FF
#define REDH 0xFF0000FF
#define YELLOWH 0xFFFF00FF
#define MAGENTAH 0xFF00FFFF
#define CYANH 0x00FFFFFF
#define BLUEH 0x0000FFFF
#define GREENH 0x00FF00FF
#define ARMYH 0x454B1BFF
#define ORANGEH 0xFF0080FF

/* MAIN WINDOW CONFIGS */
#define PIXEL_SIZE 64

/* MINIMAP CONFIGS */
#define MM_PIXEL_SIZE 16
#define SHIFT 1
#define DOT_PLAYER_SIZE 7
#define DOT_PLAYER_COLOR ORANGEH
#define RAY_COLOR REDH
#define RAY_LENGTH 16

/* PLAYER CONFIG */
#define FOV M_PI / 3

typedef struct s_draw_wall
{
	double	dist_to_wall;
	double	angle;
	double 	step_angle;		// TODO: add to main structure same all the program
	char 	orientation;
} t_draw_wall;

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
	t_vectorD	mm_c;
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
	int 		ratio;
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
	bool north;
	bool south;
	bool west;
	bool east;
	bool ceiling;
	bool floor;
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
void	mm_draw_rays(t_vars *vars, t_draw_wall *dw, int i);


/* development */
# define WHOAMI printf(GRN"Function "BMAG"%s"GRN" ran "BGRN"SUCCESSFULLY\n"RESET, __func__);