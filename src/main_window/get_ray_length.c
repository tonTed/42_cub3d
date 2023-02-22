
#include "../../include/cub3D.h"

typedef struct s_ray_length
{
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	delta_dist_x_2;
	double	delta_dist_y_2;
	double	ray_dir_x;
	double	ray_dir_y;
	int 	step_x;
	int 	step_y;
	int 	wall_x;
	int 	wall_y;
	double	map_x;
	double	map_y;
	int 	hit_wall;
	int 	side;
}				t_ray_length;

static void	set_side_dist(t_ray_length *rl, t_vars *vars)
{
	if (rl->ray_dir_x < 0)
	{
		rl->step_x = -1;
		rl->side_dist_x = (vars->p.c.X - rl->map_x) * rl->delta_dist_x;
	}
	else
	{
		rl->step_x = 1;
		rl->side_dist_x = (rl->map_x + PIXEL_SIZE - vars->p.c.X) * rl->delta_dist_x;
	}
	if (rl->ray_dir_y < 0)
	{
		rl->step_y = -1;
		rl->side_dist_y = (vars->p.c.Y - rl->map_y) * rl->delta_dist_y;
	}
	else
	{
		rl->step_y = 1;
		rl->side_dist_y = (rl->map_y + PIXEL_SIZE - vars->p.c.Y) * rl->delta_dist_y;
	}
}

static void	set_orientation(t_ray_length *rl, t_draw_wall *dw)
{
	if (rl->side == 0)
	{
		if (rl->step_x == -1)
			dw->orientation = 'W';
		else
			dw->orientation = 'E';
	}
	else
	{
		if (rl->step_y == -1)
			dw->orientation = 'N';
		else
			dw->orientation = 'S';
	}
}

static void	find_wall(t_ray_length *rl, t_vars *vars)
{
	while (!rl->hit_wall)
	{
		if (rl->side_dist_x < rl->side_dist_y)
		{
			rl->side_dist_x += rl->delta_dist_x_2;
			rl->wall_x += rl->step_x;
			rl->side = 0;
		}
		else
		{
			rl->side_dist_y += rl->delta_dist_y_2;
			rl->wall_y += rl->step_y;
			rl->side = 1;
		}
		if (vars->m.m[rl->wall_y][rl->wall_x] == 1)
			rl->hit_wall = 1;
	}
}

static void	set_data(t_ray_length *rl, t_vars *vars, t_draw_wall *dw)
{
	rl->hit_wall = 0;
	rl->ray_dir_x = cos(dw->ray_angle);
	rl->ray_dir_y = sin(dw->ray_angle);
	rl->wall_x = (int)vars->p.c.X / PIXEL_SIZE;
	rl->wall_y = (int)vars->p.c.Y / PIXEL_SIZE;
	rl->map_x = (int)vars->p.c.X / PIXEL_SIZE * PIXEL_SIZE;
	rl->map_y = (int)vars->p.c.Y / PIXEL_SIZE * PIXEL_SIZE;
	rl->delta_dist_x = fabs(1 / cos(dw->ray_angle));
	rl->delta_dist_y = fabs(1 / sin(dw->ray_angle));
	rl->delta_dist_x_2 = fabs(PIXEL_SIZE / cos(dw->ray_angle));
	rl->delta_dist_y_2 = fabs(PIXEL_SIZE / sin(dw->ray_angle));
}

double ray_length(t_draw_wall *dw, t_vars *vars)
{
	t_ray_length rl;

	set_data(&rl, vars, dw);
	set_side_dist(&rl, vars);
	find_wall(&rl, vars);
	set_orientation(&rl, dw);
	if (rl.side == 0)
		return (rl.side_dist_x - rl.delta_dist_x_2);
	else
		return (rl.side_dist_y - rl.delta_dist_y_2);
}
