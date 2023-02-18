//
// Created by Teddy BLANCO on 2023-02-13.
//

#include "../../include/cub3D.h"

void fill_image(mlx_image_t *img, int color)
{
	
	int_memset(img->pixels, color, img->height * img->width);
}