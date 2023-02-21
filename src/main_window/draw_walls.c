//
// Created by Teddy BLANCO on 2023-02-14.
//
#include "../../include/cub3D.h"

/**
 * @brief Draw walls with color
 *
 * @param vars			main struct of the program
 * @param start_ceiling	y start of the ceiling
 * @param start_floor	y start of the floor
 * @param x				x position of the wall
 *
 */
void draw_ceiling_floor_color(t_vars *vars, int start_ceiling, int start_floor, int x)
{
	while (start_ceiling > 0)
	{
		mlx_put_pixel(vars->win, x, start_ceiling, vars->a.ceiling);
		start_ceiling--;
	}
	while (start_floor < HEIGHT)
	{
		mlx_put_pixel(vars->win, x, start_floor, vars->a.floor);
		start_floor++;
	}
}

/* WORKING */

int width_next_wall(t_vars *vars, double angle, int wall_x, int wall_y)
{
	(void)vars;
	(void)angle;
	(void)wall_x;
	(void)wall_y;
	return (0);
}

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
double length_of_ray_to_wall(t_draw_wall *dw,t_vars *vars)
{
	int		hit_wall = 0;

	double	side_dist_x;
	double	side_dist_y;

	double	delta_dist_x = fabs(1 / cos(dw->ray_angle));
	double	delta_dist_y = fabs(1 / sin(dw->ray_angle));
	double	delta_dist_x_2 = fabs(64 / cos(dw->ray_angle));
	double	delta_dist_y_2 = fabs(64 / sin(dw->ray_angle));

	double	ray_dir_x = cos(dw->ray_angle);
	double	ray_dir_y = sin(dw->ray_angle);

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

	//define dw->orientation
	if (side == 0)
	{
		if (step_x == -1)
			dw->orientation = 'W';
		else
			dw->orientation = 'E';
	}
	else
	{
		if (step_y == -1)
			dw->orientation = 'N';
		else
			dw->orientation = 'S';
	}

	if (side == 0)
		return (side_dist_x - delta_dist_x_2);
	else
		return (side_dist_y - delta_dist_y_2);
}

uint32_t get_pixel_color(mlx_texture_t *texture, uint32_t x, uint32_t y) {

	uint32_t index = (y * texture->width + x) * texture->bytes_per_pixel;

	return ((int)texture->pixels[index + 0] << 0) |
		   ((int)texture->pixels[index + 1] << 8) |
		   ((int)texture->pixels[index + 2] << 16) |
		   ((int)texture->pixels[index + 3] << 24);
}

void fish_eye(t_vars *vars, t_draw_wall *dw)
{
	double ret;

	ret = vars->p.angle - dw->ray_angle;
	if (ret < 0)
		ret += 2 * M_PI;
	else if (ret > 2 * M_PI)
		ret -= 2 * M_PI;
	dw->ray_length = dw->ray_length * cos(ret);
}

void	set_wall_height_bottom_top(t_draw_wall *dw)
{
	dw->wall_height = (64 * (float) HEIGHT) / dw->ray_length;
	if (dw->wall_height > (float) HEIGHT)
		dw->wall_height = (float) HEIGHT;
	dw->wall_bottom = -dw->wall_height / 2 + HEIGHT / 2;
	if (dw->wall_bottom < 0)
		dw->wall_bottom = 0;
	dw->wall_top = dw->wall_height / 2 + HEIGHT / 2;
	if (dw->wall_top >= HEIGHT)
		dw->wall_top = HEIGHT - 1;
}

void	set_wall_x_begin(t_draw_wall *dw, t_vars *vars)
{
	if (dw->orientation == 'N' || dw->orientation == 'S')
		dw->wall_x = (int)(vars->p.c.X + dw->ray_length * cos(dw->ray_angle)) % PIXEL_SIZE;
	else
		dw->wall_x = (int)(vars->p.c.Y + dw->ray_length * sin(dw->ray_angle)) % PIXEL_SIZE;
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
void draw_vertical_line(t_draw_wall *dw, t_vars *vars, int x)
{
	fish_eye(vars, dw);
	set_wall_height_bottom_top(dw);
	set_wall_x_begin(dw, vars);

	int cpy_drawStart = dw->wall_bottom;

//	get the x of the texture
	mlx_texture_t *texture = vars->a.east_texture;
	int texture_x = dw->wall_x * texture->width / 64;

	//get the step_y to increase the y of the texture
	float step_y = texture->height / dw->wall_height;

	//draw the line
	texture_x = texture->width - texture_x;
	float texture_y = 0;

	while (dw->wall_bottom < dw->wall_top)
	{
		mlx_put_pixel(vars->win, x, dw->wall_bottom, get_pixel_color(texture, x, (int)texture_y));
		texture_y += step_y;
		dw->wall_bottom++;
	}

	(void)(texture_x);
	(void)(texture_y);
	(void)(step_y);


	// Draw ceiling and floor
	draw_ceiling_floor_color(vars, cpy_drawStart, dw->wall_bottom, x);
}

/**
 * @brief Draw walls using ray casting
 *
 * @param vars
 *
 * TODO: while loop for a ray_angle defined by the player FOV
 *
 */
void draw_walls(t_vars *vars)
{
	t_draw_wall	dw;
	int			i;

	dw.ray_angle = vars->p.angle - vars->p.fov_2;
	dw.step_angle = vars->p.fov / WIDTH;
	i = 0;
	while(i < WIDTH)
	{
		dw.ray_length = length_of_ray_to_wall(&dw , vars);
		mm_draw_rays(vars, &dw, i);
		draw_vertical_line(&dw, vars, i);
		dw.ray_angle += dw.step_angle;
		i++;
	}
}