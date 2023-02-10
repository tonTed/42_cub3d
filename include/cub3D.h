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
#define HEIGHT 704
#define TITLE "cub3d"

#define PI 3.1415926535

typedef struct s_rgb {
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_rgb;

typedef struct s_assets {
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	t_rgb	floor;
	t_rgb	ceiling;
}	t_assets;

typedef struct s_coord {
	float	x;
	float	y;
}	t_coord;

typedef struct s_player {
	t_coord coord;
	t_coord delta;
	float 	angle;
}	t_player;

typedef struct s_mmap {
	mlx_image_t *bg;
	mlx_image_t	*player;
}	t_mmap;

typedef struct s_map {
	int *map;
	int cols;
	int rows;
}	t_map;

typedef struct s_vars {
	mlx_t		*mlx;
	mlx_image_t	*bg;
	t_assets	assets;
	t_player	player;
	t_mmap		mmap;
	t_map		map;
}	t_vars;

/* hooks */
void    hook_keyboard(t_vars *vars);

/* parsing_file_map */
int32_t parsing_file_map(char *file, t_vars *vars);

/* initialization */
int32_t init(int ac, char *av[], t_vars *vars);
int32_t	init_assets(t_vars *vars);

/* utils */
void	*int_memset(void *ptr, int value, size_t num);
int		rgba_to_int(int r, int g, int b, int a);
void	free_null(void *ptr);
void	clean_exit(t_vars *vars);


/* minimap */
void	minimap(t_vars *vars);
void	draw_player_minimap(t_vars *vars);

int32_t init_assets(t_vars *vars);



/* development */
# define WHOAMI printf(GRN"Function "BMAG"%s"GRN" ran "BGRN"SUCCESSFULLY\n"RESET, __func__);