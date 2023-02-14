//
// Created by Teddy BLANCO on 2023-02-14.
//
#include "../../include/cub3D.h"

/**
 * @brief Get length of ray to wall
 *
 * @param player
 * @param angle
 * @param map
 * @param orientation	pointer to a char to define the orientation of the wall
 *
 * @return double length of ray to wall.
 *
 * TODO: use dda algorithm to get length of ray to wall
 *
 */
double length_of_ray_to_wall(t_player *player, double angle, t_map_config *map, char *orientation)
{
	(void)player;
	(void)angle;
	(void)map;
	(void)orientation;
	return (0);
}

/**
 * @brief Draw a line vertically on the screen
 *
 * @param vars
 * @param len_ray_to_wall
 * @param orientation		to knows the color to apply (N,S,E,W)
 *
 * TODO: Function to draw a line vertically on the screen
 *
 */
void draw_line_vertical(t_vars *vars, double len_ray_to_wall, char orientation)
{
	(void)vars;
	(void)len_ray_to_wall;
}

/**
 * @brief Draw walls using ray casting
 *
 * @param vars
 *
 * TODO: while loop for a angle defined by the player FOV
 *
 */
void draw_walls(t_vars *vars)
{
	double	angle;
	char	orientation;

	//loop for each angle
	double len_ray_to_wall = length_of_ray_to_wall(&vars->p, angle, &vars->m, &orientation);

	// draw a line vertically on the screen
	draw_line_vertical(vars, len_ray_to_wall, orientation);

	// draw a line in the minimap
	draw_ray(vars->mm.win, vars->p.c, angle, len_ray_to_wall, REDD);

	(void)vars;
}