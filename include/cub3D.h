/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 13:09:41 by tonted            #+#    #+#             */
/*   Updated: 2023/03/02 11:17:39 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: Norminette

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

/* FLAGS */
#define F_NORTH 0x1 // 0000 0001
#define F_SOUTH 0x2 // 0000 0010
#define F_WEST 0x4 // 0000 0100
#define F_EAST 0x8 // 0000 1000
#define F_FLOOR 0x10 // 0001 0000
#define F_CEILING 0x20 // 0010 0000
#define TOTAL 0x3F // 0011 1111
#define F_PLAYER 0x40 // 0100 0000
#define F_ERROR 0x80 // 1000 0000

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

typedef struct s_assets {
	mlx_texture_t	**textures;
	int 			colors[2];
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
	uint32_t	w;
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
	double 		fov;
	double 		fov_2;
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
	char 			flag;
}	t_vars;

/* hooks */
void    hooks(t_vars *vars);

/* parse_file */
bool	parse_file(char *file, t_vars *vars);
bool	parse_textures(t_vars *vars, int fd);
bool	parse_map(t_vars *vars, int fd, char ***buffer);

/* initialization */
bool	init(int ac, char *av[], t_vars *vars);
void	init_map(t_vars *vars, char **raw_file);
bool	is_map_closed(t_vars *vars);

/* utils */
void		*int_memset(void *ptr, int value, size_t num);
void		free_null(void *ptr);
void		clean_exit(t_vars *vars);
uint32_t	get_pixel_color(mlx_texture_t *texture, uint32_t x, uint32_t y);
int			gnl(int fd, char **line);
void		remove_spaces(char **line);
void		add_line_tabstr(char ***tabstr, char *line);

/* utils image */
void	fill_image(mlx_image_t *img, int color);

/* utils draw */
void 	draw_walls(t_vars *vars);
void	draw_dot(int size, int color, mlx_image_t *win, t_vectorD pos);
void	draw_ray(mlx_image_t *win, t_vectorD pos, double angle, int length);

double	ray_length(t_draw_wall *dw, t_vars *vars);

/* draw */
void	draw_main_window(t_vars *vars);
void	draw_minimap(t_vars *vars);
void	draw_bonus(t_vars *vars);
void	mm_draw_rays(t_vars *vars, t_draw_wall *dw, int i);

/* utils main windows */
void	set_begin_vector_texture(t_vars *vars, t_draw_wall *dw);
void	set_wall_x_begin(t_draw_wall *dw, t_vars *vars);
void	set_wall_height_bottom_top(t_draw_wall *dw, u_int32_t height);

/* utils minimap */
void mm_draw_squares(t_vars *vars);

/* clean exit */
int	clean_textures(t_vars *vars, int ret, char *msg);
int	clean_map(t_vars *vars, int ret, char *msg);


/* development */
# define WHOAMI printf(GRN"Function "BMAG"%s"GRN" ran "BGRN"SUCCESSFULLY\n"RESET, __func__);