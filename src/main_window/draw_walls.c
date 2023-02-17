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
double length_of_ray_to_wall(t_vars *vars, double angle)
{
	int hit_wall = 0;
	int wall_x, wall_y;
	double ray_x = vars->p.c.X;
	double ray_y = vars->p.c.Y;

	while (!hit_wall && ray_x >= 0 && ray_x < (vars->m.s.w * 64) && ray_y >= 0 && ray_y < (vars->m.s.h * 64))
	{
		wall_x = (int)ray_x / 64;
		wall_y = (int)ray_y / 64;
		if (vars->m.m[wall_y][wall_x] == 1)
		{
			hit_wall = 1;
		}
		else
		{
			ray_x += cos(angle);
			ray_y += sin(angle);
		}
	}

	double dist_to_wall = 0;

	if (hit_wall)
	{
		double dist_x = ray_x - vars->p.c.X;
		double dist_y = ray_y - vars->p.c.Y;
		dist_to_wall = sqrt(dist_x * dist_x + dist_y * dist_y);
	}

	return (dist_to_wall);
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
	double dist_to_wall;
	// double angle_right = vars->p.angle + FOV / 2;
	double angle_left = vars->p.angle - FOV / 2;
	// dist_to_wall = length_of_ray_to_wall(vars, angle_left);
	// draw_ray(vars->mm.win, vars->p.c, angle_left, dist_to_wall, YELLOW);
	// dist_to_wall = length_of_ray_to_wall(vars, vars->p.angle);
	// draw_ray(vars->mm.win, vars->p.c, vars->p.angle, dist_to_wall, YELLOW);
	// dist_to_wall = length_of_ray_to_wall(vars, angle_right);
	// draw_ray(vars->mm.win, vars->p.c, angle_right, dist_to_wall, YELLOW);
	int i = 0;
	int nb_of_rays = 120;
	while(i < nb_of_rays)
	{
		dist_to_wall = length_of_ray_to_wall(vars, angle_left);
		draw_ray(vars->mm.win, vars->p.c, angle_left, dist_to_wall, YELLOW);
		angle_left += FOV/nb_of_rays;
		i++;
	}
/*
	//loop for each angle
	double len_ray_to_wall = length_of_ray_to_wall(&vars->p, angle, &vars->m, &orientation);

	// draw a line vertically on the screen
	draw_line_vertical(vars, len_ray_to_wall, orientation);

	// draw a line in the minimap
	draw_ray(vars->mm.win, vars->p.c, angle, len_ray_to_wall, REDD);

	(void)vars;
 */

}