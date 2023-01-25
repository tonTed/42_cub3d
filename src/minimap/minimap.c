
#include "../../include/cub3D.h"

void	mock_init(t_vars *vars)
{
	vars->map.cols = 8;
	vars->map.rows = 8;
	vars->map.map = (int *)malloc(vars->map.rows * vars->map.cols * sizeof(int));

	vars->mmap.bg = mlx_new_image(vars->mlx, WIDTH - 50, HEIGHT - 50);
	int_memset(vars->mmap.bg->pixels, rgba_to_int(100, 100, 100, 255),
			   vars->mmap.bg->width * vars->mmap.bg->height);
	mlx_image_to_window(vars->mlx, vars->mmap.bg, 25, 25);

	vars->player.coord.x = 300;
	vars->player.coord.y = 300;

	vars->mmap.player = mlx_new_image(vars->mlx, 8, 8);
	int_memset(vars->mmap.player->pixels, rgba_to_int(255, 255, 255, 255),
			   vars->mmap.player->width * vars->mmap.player->height);
	mlx_image_to_window(vars->mlx, vars->mmap.player, vars->player.coord.x - 4, vars->player.coord.y - 4);
}

void	minimap(t_vars *vars)
{
	mock_init(vars);
	(void)vars;
}