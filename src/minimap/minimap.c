
#include "../../include/cub3D.h"


// b / g / r
#define MMAP_SIZE 64
#define MMAP_COLS 8
#define MMAP_ROWS 8
#define MMAP_BLACK 0xFF000000
#define MMAP_WHITE 0xFFFFFFFF
#define MMAP_YELLOW 0x0000FFFF
#define MMAP_ORANGE 0xFF0080FF
#define MMAP_RED 0xFF0000FF

void	set_big_pixel(void *img, int color)
{
	int y = 1;

	while (y < MMAP_SIZE - 1)
	{
		int_memset(&img[y * MMAP_COLS * MMAP_SIZE * 4], color, MMAP_SIZE - 2);
		y++;
	}
}

/**
 *
 * from	MMAP_SIZE * MMAP_SIZE * MMAP_COLS * y * 4 + MMAP_SIZE * 4 * x
 * to	(4 * MMAP_SIZE) * (MMAP_SIZE * MMAP_COLS * y + x)
 *
 * @param img
 * @param map
 */
void	set_minimap_img(mlx_image_t *img, int *map)
{
	int x;
	int y;

	y = 0;
	while (y < MMAP_ROWS)
	{
		x = 0;
		while (x < MMAP_COLS)
		{
			if (map[x + y * MMAP_COLS] == 1)
			{
				set_big_pixel(&img->pixels[(4 * MMAP_SIZE)
					* (MMAP_SIZE * MMAP_COLS * y + x)], MMAP_WHITE);
			}
			else
			{
				set_big_pixel(&img->pixels[(4 * MMAP_SIZE)
					* (MMAP_SIZE * MMAP_COLS * y + x)], MMAP_BLACK);
			}
			x++;
		}
		y++;
	}
}

int map[]=
{
1,1,1,1,1,1,1,1,
1,0,1,0,0,0,0,1,
1,0,1,0,0,0,0,1,
1,0,1,0,0,0,0,1,
1,0,0,0,0,0,0,1,
1,0,0,0,0,1,0,1,
1,0,0,0,0,0,0,1,
1,1,1,1,1,1,1,1,
};

void	mock_init(t_vars *vars)
{
	vars->map.cols = 8;
	vars->map.rows = 8;
//	vars->map.map = (int *)malloc(vars->map.rows * vars->map.cols * sizeof(int));
	vars->map.map = map;

	vars->mmap.bg = mlx_new_image(vars->mlx, MMAP_COLS * MMAP_SIZE, MMAP_ROWS * MMAP_SIZE);

	set_minimap_img(vars->mmap.bg, vars->map.map);
	mlx_image_to_window(vars->mlx, vars->mmap.bg, 0, 0);

	vars->player.coord.x = 300;
	vars->player.coord.y = 300;
	vars->player.angle = PI / 2;
	vars->player.delta.x = cos(vars->player.angle) * 5;
	vars->player.delta.y = sin(vars->player.angle) * 5;

	vars->mmap.player = mlx_new_image(vars->mlx, 8, 8);
	int_memset(vars->mmap.player->pixels, MMAP_YELLOW,
			   vars->mmap.player->width * vars->mmap.player->height);
	mlx_image_to_window(vars->mlx, vars->mmap.player, vars->player.coord.x - 4, vars->player.coord.y - 4);
}

void	minimap(t_vars *vars)
{
	mock_init(vars);
	(void)vars;
}


void	draw_player_minimap(t_vars *vars)
{
	int x = (int)vars->player.coord.x - 4;
	int y = (int)vars->player.coord.y - 4;

	int i = 0;

	set_minimap_img(vars->mmap.bg, map);

	while (i < 8)
	{
//		int_memset(&vars->mmap.bg->pixels[(MMAP_SIZE * MMAP_COLS * 4) * i], MMAP_ORANGE, 64);
		int_memset(&vars->mmap.bg->pixels[((y * 64 * 8 * 4) + x * 4) + i * 64 * 8 * 4], MMAP_ORANGE, 8);
		i++;
	}
}