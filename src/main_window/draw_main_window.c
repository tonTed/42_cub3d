#include "../../include/cub3D.h"

/**
 * @brief Draw ceiling or floor before drawing the walls. 1/2 top ceiling, 1/2 bottom floor.
 *
 * @param vars
 *
 * TODO: Function to draw ceiling and floor
 */
void draw_ceiling_floor_color(t_vars *vars)
{
//	int median = vars->win->width * vars->win->height/2;
//	int_memset(vars->win->pixels, GREY, median);
//	int_memset(&vars->win->pixels[median * 4] , WHITE, median);
	(void)vars;
}

/**
 * @brief Draw walls with color
 *
 * @param vars
 *
 * TODO: Function to draw walls with color
 * TODO: Remove this function and use draw_walls_texture instead
 */
void draw_walls_color(t_vars *vars)
{
	(void)vars;
}

/**
 * @brief Draw walls with texture
 *
 * @param vars
 *
 * TODO: Function to draw walls with texture
 */
void draw_walls_texture(t_vars *vars)
{
	(void)vars;
}

void draw_main_window(t_vars *vars)
{
	draw_ceiling_floor_color(vars);
	draw_walls(vars);
}