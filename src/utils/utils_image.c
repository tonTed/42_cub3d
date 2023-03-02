/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 11:23:17 by tonted            #+#    #+#             */
/*   Updated: 2023/03/02 11:24:10 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/**
 * @brief Full an image with a color.
 * 
 * @param img	pointer to the image
 * @param color	color to fill the image with
 */
void	fill_image(mlx_image_t *img, int color)
{
	int_memset(img->pixels, color, img->height * img->width);
}
