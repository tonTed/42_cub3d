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
double length_of_ray_to_wall(t_vars *vars, double angle, char *orientation)
{
	int		hit_wall = 0;

	double	side_dist_x;
	double	side_dist_y;

	double	delta_dist_x = fabs(1 / cos(angle));
	double	delta_dist_y = fabs(1 / sin(angle));
	double	delta_dist_x_2 = fabs(64 / cos(angle));
	double	delta_dist_y_2 = fabs(64 / sin(angle));

	double	ray_dir_x = cos(angle);
	double	ray_dir_y = sin(angle);

	int 	step_x;
	int 	step_y;

	int 	wall_x = (int)vars->p.c.X / 64;
	int 	wall_y = (int)vars->p.c.Y / 64;

	double	map_x = (int)vars->p.c.X / 64 * 64;
	double	map_y = (int)vars->p.c.Y / 64 * 64;

	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (vars->p.c.X - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 64 - vars->p.c.X) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (vars->p.c.Y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 64 - vars->p.c.Y) * delta_dist_y;
	}

	int side;

	while (!hit_wall)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x_2;
			wall_x += step_x;
			side = 0;

		}
		else
		{
			side_dist_y += delta_dist_y_2;
			wall_y += step_y;
			side = 1;
		}
		if (vars->m.m[wall_y][wall_x] == 1)
			hit_wall = 1;
	}

	//define orientation
	if (side == 0)
	{
		if (step_x == -1)
			*orientation = 'W';
		else
			*orientation = 'E';
	}
	else
	{
		if (step_y == -1)
			*orientation = 'N';
		else
			*orientation = 'S';
	}

	if (side == 0)
		return (side_dist_x - delta_dist_x_2);
	else
		return (side_dist_y - delta_dist_y_2);
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
void draw_line_vertical(t_vars *vars, double len_ray_to_wall, char orientation, int y, double angle_left )
{

	int color;
	if (orientation == 'N')
		color = 0xd3ab9eff;
	else if (orientation == 'S')
		color = 0xffee93ff;
	else if (orientation == 'E')
		color = 0xa0ced9ff;
	else if (orientation == 'W')
		color = 0xadf7b6ff;
	float ca = vars->p.angle-angle_left;
	if ( ca < 0){
		ca += 2* M_PI;
	}
	if (ca > 2 * M_PI){
		ca -= 2 * M_PI;
	}
	// Manage the fisheye effect
	len_ray_to_wall = len_ray_to_wall * cos(ca);

	// Calculate height of line to draw on screen
	float lineH = (64 * (float)HEIGHT)/len_ray_to_wall;

	// Make sure line is not too big
	if (lineH > (float)HEIGHT)
		lineH = (float)HEIGHT;

	// TODO: fix for manage overflows (even numbers)

	// Calculate the median of the line
	int half_wall = lineH / 2;

	// Draw the line color by color
	int i = 0;
	while(i < half_wall)
	{
		for (int j = 0; j < 64; j++){
		mlx_put_pixel(vars->win, y, HEIGHT/2 + i + j, color);
		mlx_put_pixel(vars->win, y, HEIGHT/2 - i + j, color);
		}
		i++;
	}

	//draw the line with texture
	//get the x of the wall to get the beginning of the texture
	int wall_x;
	if (orientation == 'N' || orientation == 'S')
		wall_x = (int)(vars->p.c.X + len_ray_to_wall * cos(angle_left)) % 64;
	else
		wall_x = (int)(vars->p.c.Y + len_ray_to_wall * sin(angle_left)) % 64;

	//get the x of the texture
	mlx_texture_t *texture = vars->a.east_texture;
	int texture_x = wall_x * texture->width / 64;

	printf("width: %d ,texture_x = %d, wall_x = %d\n",texture->width ,texture_x, wall_x);
	exit(EXIT_FAILURE);







	// Draw the top and bottom of the screen (ceiling and floor)
	 while (i < HEIGHT/2){
	 	for (int j = 0; j < 64; j++){
	 	mlx_put_pixel(vars->win, y, HEIGHT/2 + i + j, BLACK);
	 	mlx_put_pixel(vars->win, y, HEIGHT/2 - i + j, WHITE);
	 	}
	 	i++;
	 }
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
	int i = 0;
	int nb_of_rays = 1024;
	double angle_left = vars->p.angle - FOV / 2;

	char orientation;

	t_vectorD tmp;
	tmp.X = vars->p.c.X / 4;
	tmp.Y = vars->p.c.Y / 4;

	while(i < nb_of_rays)
	{
		dist_to_wall = length_of_ray_to_wall(vars, angle_left, &orientation);
		 if ( i % 32 == 0)
			draw_ray(vars->mm.win, tmp, angle_left, dist_to_wall / 4, REDD);
		draw_line_vertical(vars, dist_to_wall, orientation, i, angle_left);
		angle_left += FOV/nb_of_rays;
		i++;
	}
//	exit(EXIT_SUCCESS);
}