#include "../include/cub3D.h"

#define mapWidth 8
#define mapHeight 8
#define squareSize 64
#define screenWidth mapWidth * squareSize
#define screenHeight mapHeight * squareSize

#define BLACK 0xFF000000
#define WHITE 0xFFFFFFFF
#define YELLOW 0xFF00FFFF
#define ORANGE 0xFF0080FF
#define REDD 0xFF0000FF
#define GREY 0xFF969696

#define PI 3.1415926535

int worldMap[mapHeight][mapWidth]=
		{
		{1,1,1,1,1,1,1,1},
		{1,0,1,0,0,0,0,1},
		{1,0,1,0,0,0,0,1},
		{1,0,1,0,0,0,0,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,0,1,0,1},
		{1,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1},
		};

typedef struct s_vecDbl
{
	double	X;
	double	Y;
}	t_vecDbl;

typedef struct s_vecInt
{
	int	X;
	int	Y;
}	t_vecInt;

typedef struct s_play
{
	t_vecDbl	c;
	t_vecDbl	dir;
    t_vecDbl    left_FOV;
    t_vecDbl    right_FOV;
	double		a;

} t_play;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*win;
	t_play 		p;
}	t_data;

void	fill_img_color(mlx_image_t *img, int color)
{
	int_memset(img->pixels, color, img->height * img->height);
}

uint32_t get_index(t_vecInt c, int size, int cols)
{
	return (size * size * cols * c.Y * 4 + size * c.X * 4);
}

void	minimap_draw_square(t_data *d, t_vecInt c)
{
	int row;
	int index;

	row = 1;
	while (row < squareSize - 1)
	{
		index = get_index(c, squareSize, mapWidth) + (row * squareSize * mapWidth * 4);
		if (worldMap[c.Y][c.X] == 1)
			int_memset(&d->win->pixels[index + 4], BLACK, squareSize - 2);
		else
			int_memset(&d->win->pixels[index + 4], WHITE, squareSize - 2);
		row++;
	}
}

void	minimap_draw_squares(t_data *d)
{
	t_vecInt 	coord;

	coord.Y = 0;
	while (coord.Y < mapHeight)
	{
		coord.X = 0;
		while (coord.X < mapWidth)
		{
			minimap_draw_square(d, coord);
			coord.X++;
		}
		coord.Y++;
	}
}

// always odd
#define MMAP_PLAYER_DOT	9
#define MMAP_DIR_DOT 5

int 	img_len_row(mlx_image_t *img)
{
	return (img->width * 4);
}

double get_dir_Y(t_play p)
{
	return (p.c.Y + p.dir.Y * squareSize);
}

double get_dir_X(t_play p)
{
	return (p.c.X + p.dir.X * squareSize);
}

void draw_line(t_data *d, t_vecDbl v1, t_vecDbl v2)
{
	int dx, dy, x, y, x_inc, y_inc, error, index;

	dx = abs((int)v2.X - (int)v1.X);
	dy = abs((int)v2.Y - (int)v1.Y);

	x = (int)v1.X;
	y = (int)v1.Y;

	if((int)v2.X >= (int)v1.X)
		x_inc = 1;
	else
		x_inc = -1;

	if((int)v2.Y >= (int)v1.Y)
		y_inc = 1;
	else
		y_inc = -1;

	error = dx - dy;

	int_memset(&d->win->pixels[d->win->width * 4 * y + x * 4], REDD, 1);

	for(index = 0; index < dx + dy; index++)
	{
		if(error < 0)
		{
			error += dx;
			y += y_inc;
		}
		else
		{
			error -= dy;
			x += x_inc;
		}
//		printf("index: %d\tdx + dy: %d\tx: %d\ty: %d\tdirX: %d\tdirY: %d\n", index, dx+dy, x, y,
//			   (int)get_dir_X(d->p), (int) get_dir_Y(d->p));
		int_memset(&d->win->pixels[d->win->width * 4 * y + x * 4], REDD, 1);
//		mlx_pixel_put(mlx, x, y, 0xFFFFFF);
	}
}

void	minimap_draw_player(t_data *d)
{
	int row;
	int med;
	int index;

	med = MMAP_PLAYER_DOT / 2;
	row = -med;
	while (row <= med)
	{
		index = (d->win->width * 4) * ((int)d->p.c.Y + row) + ((int)d->p.c.X * 4) + (abs(row % MMAP_PLAYER_DOT) - med) * 4;
		int_memset(&d->win->pixels[index], ORANGE, MMAP_PLAYER_DOT - abs(row % MMAP_PLAYER_DOT) * 2);
		row++;
	}

	med = MMAP_DIR_DOT / 2;
	row = -med;
	while (row <= med)
	{
		index = (d->win->width * 4) * ((int)get_dir_Y(d->p) + row) + ((int)get_dir_X(d->p) * 4) + (abs(row % MMAP_DIR_DOT) - med) * 4;
		int_memset(&d->win->pixels[index], REDD, MMAP_DIR_DOT - abs(row % MMAP_DIR_DOT) * 2);
		row++;
	}

    // Draw ray player
    t_vecDbl tmp;
    tmp.X = get_dir_X(d->p);
    tmp.Y = get_dir_Y(d->p);
	draw_line(d, d->p.c, tmp);
	double planeX = 0, planeY = 0.66;

	for(int x = 0; x < 8; x++)
    {
      //calculate ray position and direction
		double cameraX = 2 * x / 8.0 - 1; //x-coordinate in camera space
		double rayDirX = d->p.dir.X + planeX * cameraX;
		double rayDirY = d->p.dir.Y + planeY * cameraX;

		//which box of the map we're in
		int mapX = (int)d->p.c.X / squareSize;
		int mapY = (int)d->p.c.Y / squareSize;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

//		length of ray from one x or y-side to next x or y-side
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		double perpWallDist;
//
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;
//
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = ((d->p.c.X - (double)mapX * 64.0) * deltaDistX);
		}
		else
		{
			stepX = 1;
			sideDistX = (((double)mapX + 1) * 64.0 - d->p.c.X) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (d->p.c.Y - (double)mapY * 64.0) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (((double)mapY + 1) * 64 - d->p.c.Y) * deltaDistY;
		}
//		printf("x: %d\t rayDirX: %f\trayDirY: %f\tstepX: %d\tstepY: %d\tsideDistX: %f\tsideDistY: %f\n", x , rayDirX, rayDirY, stepX, stepY, sideDistX, sideDistY);
		//perform DDA
		double length;
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				length = sideDistX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				length = sideDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[mapY][mapX] > 0) hit = 1;
		}
		printf("x: %d\tmapX: %d\tmapY: %d\t hit: %d\n", x, mapX, mapY, hit);

		t_vecDbl tmpp;

		tmpp.X = d->p.c.X + length * rayDirX;
		tmpp.Y = d->p.c.Y + length * rayDirY;
		draw_line(d, d->p.c, tmpp);

	}
//	exit(0);

    // // Draw ray left FOV
    // t_vecDbl left_fov;
    // left_fov.X = d->p.c.X + d->p.left_FOV.X * squareSize;
    // left_fov.Y = d->p.c.Y + d->p.left_FOV.Y * squareSize;
	// draw_line(d, d->p.c, left_fov);

    // // Draw ray right FOV
    // t_vecDbl right_fov;
    // right_fov.X = d->p.c.X + d->p.right_FOV.X * squareSize;
    // right_fov.Y = d->p.c.Y + d->p.right_FOV.Y * squareSize;
	// draw_line(d, d->p.c, right_fov);

}

void	keyboard_hook(t_data *d)
{
	double rotSpeed = 0.05;
	double moveSpeed = 1;

	if (mlx_is_key_down(d->mlx, MLX_KEY_LEFT))
	{
		double oldDirX = d->p.dir.X;
		double oldLeftFOVX = d->p.left_FOV.X;
		double oldRightFOVX = d->p.right_FOV.X;

		d->p.dir.X = d->p.dir.X * cos(-rotSpeed) - d->p.dir.Y * sin(-rotSpeed);
		d->p.dir.Y = oldDirX * sin(-rotSpeed) + d->p.dir.Y * cos(-rotSpeed);

		d->p.left_FOV.X = d->p.left_FOV.X * cos(-rotSpeed) - d->p.left_FOV.Y * sin(-rotSpeed);
		d->p.left_FOV.Y = oldLeftFOVX * sin(-rotSpeed) + d->p.left_FOV.Y * cos(-rotSpeed);

		d->p.right_FOV.X = d->p.right_FOV.X * cos(-rotSpeed) - d->p.right_FOV.Y * sin(-rotSpeed);
		d->p.right_FOV.Y = oldRightFOVX * sin(-rotSpeed) + d->p.right_FOV.Y * cos(-rotSpeed);
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_RIGHT))
	{
		double oldDirX = d->p.dir.X;
		double oldLeftFOVX = d->p.left_FOV.X;
		double oldRightFOVX = d->p.right_FOV.X;

		d->p.dir.X = d->p.dir.X * cos(rotSpeed) - d->p.dir.Y * sin(rotSpeed);
		d->p.dir.Y = oldDirX * sin(rotSpeed) + d->p.dir.Y * cos(rotSpeed);

		d->p.left_FOV.X = d->p.left_FOV.X * cos(rotSpeed) - d->p.left_FOV.Y * sin(rotSpeed);
		d->p.left_FOV.Y = oldLeftFOVX * sin(rotSpeed) + d->p.left_FOV.Y * cos(rotSpeed);

		d->p.right_FOV.X = d->p.right_FOV.X * cos(rotSpeed) - d->p.right_FOV.Y * sin(rotSpeed);
		d->p.right_FOV.Y = oldRightFOVX * sin(rotSpeed) + d->p.right_FOV.Y * cos(rotSpeed);
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_W))
	{
		d->p.c.X += d->p.dir.X * moveSpeed;
		d->p.c.Y += d->p.dir.Y * moveSpeed;
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_S))
	{
		d->p.c.X -= d->p.dir.X * moveSpeed;
		d->p.c.Y -= d->p.dir.Y * moveSpeed;
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_A))
	{
		d->p.c.X += d->p.dir.Y * moveSpeed;
		d->p.c.Y -= d->p.dir.X * moveSpeed;
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_D))
	{
		d->p.c.X -= d->p.dir.Y * moveSpeed;
		d->p.c.Y += d->p.dir.X * moveSpeed;
	}
}

void	cub_loop(void *data)
{
	t_data *d = data;

	//background
	fill_img_color(d->win, GREY);

	//cells
	minimap_draw_squares(d);

	//player
	minimap_draw_player(d);

	//keyboard_hook
	keyboard_hook(d);


}
/*
 * EAST		-> 2 * PI / 0
 * NORTH	-> PI/2
 * WEST		-> PI
 * SUD		-> 3 * PI / 2
 * */
void	init_data(t_data *d)
{

	d->mlx = mlx_init(screenHeight, screenHeight, "playground", false);
	d->win = mlx_new_image(d->mlx, screenWidth, screenHeight);

	d->p.c.X = 300;
	d->p.c.Y = 300;

	d->p.dir.X = 0;
	d->p.dir.Y = -1;

	d->p.left_FOV.X = d->p.dir.X - 0.66;
	d->p.left_FOV.Y = d->p.dir.Y;
	d->p.right_FOV.X = d->p.dir.X + 0.66;
	d->p.right_FOV.Y = d->p.dir.Y;

	d->p.a = PI / 2;
}

int main2(void)
{
	t_data data;

	init_data(&data);
	mlx_image_to_window(data.mlx, data.win, 0, 0);
	mlx_loop_hook(data.mlx, &cub_loop, (void *)&data);
	mlx_loop(data.mlx);

	mlx_terminate(data.mlx);

	return (EXIT_SUCCESS);
}