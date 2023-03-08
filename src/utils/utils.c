/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 11:24:44 by tonted            #+#    #+#             */
/*   Updated: 2023/03/02 11:28:39 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	*int_memset(void *ptr, int value, size_t num)
{
	int		*int_ptr;
	size_t	i;

	int_ptr = (int *)ptr;
	i = 0;
	while (i < num)
		int_ptr[i++] = value;
	return (ptr);
}

int	rgba_to_int(int r, int g, int b, int a)
{
	return ((a << 24) | (r << 16) | (g << 8) | b);
}

uint32_t	get_pixel_color(mlx_texture_t *texture, uint32_t x, uint32_t y)
{
	uint32_t	index;

	index = (y * texture->width + x) * texture->bytes_per_pixel;
	return (((int)texture->pixels[index + 3] << 0)
		| ((int)texture->pixels[index + 2] << 8)
		| ((int)texture->pixels[index + 1] << 16)
		| ((int)texture->pixels[index + 0] << 24));
}

void	free_null(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	remove_spaces(char **line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (*line)
	{
		while ((*line)[i])
		{
			if ((*line)[i] != ' ')
				(*line)[j++] = (*line)[i];
			i++;
		}
		(*line)[j] = '\0';
	}
}
