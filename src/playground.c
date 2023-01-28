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

int worldMap[mapWidth][mapHeight]=
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
	double		a;
	
} t_play;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*win;
	t_play 		p;
}	t_data;

//void	cub_loop(void *data)
//{
//	t_data *d = data;
//	int x = 0;
//
//	while (x < mapWidth)
//	{
//		//calculer la position et la directio du rayon
//		double camX = 2 * x / (double) mapWidth - 1; //coordonnée x dans l'espace caméra
//		double rayDirX = d->dirX + d->planeX * camX;
//		double rayDirY = d->dirY + d->planeY * camX;
//		printf("x: %d\tcamX: %f\trayDirX: %f\trayDirY: %f\n", x, camX, rayDirX, rayDirY);
//
//		//dans quelle case de la carte nous sommes
//		int mapX = (int)d->posX;
//		int mapY = (int)d->posY;
//
//		//longueur du rayon de la position actuelle au côté x ou y suivant
//		double sideDistX ;
//		double sideDistY ;
//
//		//longueur du rayon d'un côté x ou y au côté x ou y suivant
//		double deltaDistX = (rayDirX == 0) ? 1e30 : abs(1 / rayDirX);
//		double deltaDistY = (rayDirY == 0) ? 1e30 : abs(1 / rayDirY);
//
//		double perpWallDist ;
//
//		//dans quelle direction aller dans la direction x ou y (soit +1 ou -1)
//		int stepX ;
//		int stepY ;
//
//		int hit = 0 ; // y a-t-il eu un coup de mur ?
//
//		// est-ce qu'un mur NS ou EW a été touché ?
//		int side ;
//
//		//calculate step and initial sideDist
//		if (rayDirX < 0)
//		{
//			stepX = -1;
//			sideDistX = (d->posX - mapX) * deltaDistX;
//		}
//		else
//		{
//			stepX = 1;
//			sideDistX = (mapX + 1.0 - d->posX) * deltaDistX;
//		}
//		if (rayDirY < 0)
//		{
//			stepY = -1;
//			sideDistY = (d->posY - mapY) * deltaDistY;
//		}
//		else
//		{
//			stepY = 1;
//			sideDistY = (mapY + 1.0 - d->posY) * deltaDistY;
//		}
//
//		x++;
//
//	//perform DDA
//	while (hit == 0)
//	{
//		//jump to next map square, either in x-direction, or in y-direction
//		if (sideDistX < sideDistY)
//		{
//			sideDistX += deltaDistX;
//			mapX += stepX;
//			side = 0;
//		}
//		else
//		{
//			sideDistY += deltaDistY;
//			mapY += stepY;
//			side = 1;
//		}
//		//Check if ray has hit a wall
//		if (worldMap[mapX][mapY] > 0)
//			hit = 1;
//	}
//
//	//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
//	if(side == 0)
//		perpWallDist = (sideDistX - deltaDistX);
//	else
//		perpWallDist = (sideDistY - deltaDistY);
//
//	exit(0);
//	}
//}

//int main(void)
//{
//	t_data d;
//	d.posX = 22, d.posY = 12;		//x et y position de départ
//	d.dirX = -1, d.dirY = 0;		//vecteur direction initial
//	d.planeX = 0, d.planeY = 0.66;	//la version 2d raycaster du plan caméra
//
//	mlx_t	*mlx = mlx_init(screenHeight, screenHeight, "raycasting", false);
//	mlx_loop_hook(mlx, &cub_loop, (void *)&d);
//
//	mlx_loop(mlx);
//
//	return (EXIT_SUCCESS);
//}

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

	v2.X = get_dir_X(d->p);
	v2.Y = get_dir_Y(d->p);

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

	draw_line(d, d->p.c, d->p.dir);
}

void	keyboard_hook(t_data *d)
{
	double rotSpeed = 0.05;
	double moveSpeed = 1;

	if (mlx_is_key_down(d->mlx, MLX_KEY_LEFT))
	{
		double oldDirX = d->p.dir.X;
		d->p.dir.X = d->p.dir.X * cos(-rotSpeed) - d->p.dir.Y * sin(-rotSpeed);
		d->p.dir.Y = oldDirX * sin(-rotSpeed) + d->p.dir.Y * cos(-rotSpeed);
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_RIGHT))
	{
		double oldDirX = d->p.dir.X;
		d->p.dir.X = d->p.dir.X * cos(rotSpeed) - d->p.dir.Y * sin(rotSpeed);
		d->p.dir.Y = oldDirX * sin(rotSpeed) + d->p.dir.Y * cos(rotSpeed);
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

	d->p.a = PI / 2;
}

int main(void)
{
	t_data data;

	init_data(&data);
	mlx_image_to_window(data.mlx, data.win, 0, 0);
	mlx_loop_hook(data.mlx, &cub_loop, (void *)&data);
	mlx_loop(data.mlx);

	mlx_terminate(data.mlx);

	return (EXIT_SUCCESS);
}