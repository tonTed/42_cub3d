#include "../include/cub3D.h"

#define mapWidth 8
#define mapHeight 8
#define squareSize 64
#define screenWidth mapWidth * squareSize
#define screenHeight mapHeight * squareSize

#define BLACK 0xFF000000
#define WHITE 0xFFFFFFFF
#define YELLOW 0x0000FFFF
#define ORANGE 0xFF0080FF
#define REDD 0xFF0000FF
#define GREY 0xFF969696

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

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*win;
	t_vecDbl	p;
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

uint32_t get_index_dbl(t_vecDbl c, int sizeW, int sizeH, int cols)
{
	return (sizeW * sizeH * cols * c.Y * 4 + sizeH * c.X * 4);
}

void	minimap_draw_square(t_data *d, t_vecInt c)
{
	int row;
	int index;

	row = 1;
	while (row < squareSize - 1)
	{
		index = get_index(c, squareSize, mapWidth) + (row * squareSize * mapWidth * 4);
//		printf("index: %d\n", index);
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

#define MMAP_PLAYER_DOT	9

void	minimap_draw_player(t_data *d)
{
	int row;
	int med;
	int index;

	med = MMAP_PLAYER_DOT / 2;
	row = -med;
	while (row <= med)
	{
		index = d->win->width * 4 * (d->p.Y + row) + d->p.X * 4 + (abs(row % MMAP_PLAYER_DOT) - 4) * 4;
		int_memset(&d->win->pixels[index], ORANGE, MMAP_PLAYER_DOT - abs(row % MMAP_PLAYER_DOT) * 2);
		row++;
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

}

void	init_data(t_data *d)
{

	d->mlx = mlx_init(screenHeight, screenHeight, "playground", false);
	d->win = mlx_new_image(d->mlx, screenWidth, screenHeight);

	d->p.X = 300;
	d->p.Y = 300;
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