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

uint32_t get_pixel_color(mlx_texture_t *texture, uint32_t x, uint32_t y) {

	uint32_t index = (y * texture->width + x) * texture->bytes_per_pixel;

	return ((int)texture->pixels[index + 3] << 0) |
		   ((int)texture->pixels[index + 2] << 8) |
		   ((int)texture->pixels[index + 1] << 16) |
		   ((int)texture->pixels[index + 0] << 24);
}

void	fish_eye(t_vars *vars, t_draw_wall *dw)
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
	dw->wall_top = -dw->wall_height / 2 + HEIGHT / 2;
	if (dw->wall_top < 0)
		dw->wall_top = 0;
	dw->wall_bottom = dw->wall_height / 2 + HEIGHT / 2;
	if (dw->wall_bottom >= HEIGHT)
		dw->wall_bottom = HEIGHT - 1;
}

void	set_wall_x_begin(t_draw_wall *dw, t_vars *vars)
{
	if (dw->orientation == NORTH || dw->orientation == SOUTH)
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
void	draw_vertical_line(t_draw_wall *dw, t_vars *vars, int x)
{
	int tmp_wall_bottom;

	fish_eye(vars, dw);
	set_wall_height_bottom_top(dw);
	set_wall_x_begin(dw, vars);
	tmp_wall_bottom = dw->wall_bottom;

	//	get the x of the texture
	int texture_x = dw->wall_x * vars->a.textures[dw->orientation]->width / PIXEL_SIZE;

	//get the step_y to increase the y of the texture
	float step_y = vars->a.textures[dw->orientation]->height / dw->wall_height;

	//draw the line
	texture_x = vars->a.textures[dw->orientation]->width - texture_x;
	float texture_y = vars->a.textures[dw->orientation]->height - 1;

	while (dw->wall_bottom > dw->wall_top)
	{
		mlx_put_pixel(vars->win, x, dw->wall_bottom,
					  get_pixel_color(vars->a.textures[dw->orientation], texture_x, (int)texture_y));
		texture_y -= step_y; // TODO: check if texture_y is not negative
		dw->wall_bottom--;
	}

	dw->wall_bottom = tmp_wall_bottom;
	draw_ceiling_floor_color(vars, dw->wall_top, dw->wall_bottom, x);
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
		dw.ray_length = ray_length(&dw, vars);
		mm_draw_rays(vars, &dw, i);
		draw_vertical_line(&dw, vars, i);
		dw.ray_angle += dw.step_angle;
		i++;
	}
}