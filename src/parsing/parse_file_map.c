/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:03:33 by tonted            #+#    #+#             */
/*   Updated: 2023/02/22 23:54:57 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"
#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief Parse the file map and fill the vars struct
 *
 * @param file	path to the file
 * @param vars	pointer to the global vars struct
 *
 * @return EXIT_SUCCESS if success, EXIT_FAILURE if error.
 *
 * TODO: check if the file is valid.
 * 	ERRORS to manage:
 * 		- [] extension is not .cub
 * 		- [] file can't be open (do function reusable for other files).
 *
 * TODO: parsing assets description and set [[vars->a]]
 * 	ERRORS to manage:
 * 		- [] missing data (use flag) [NO, SO, WE, EA, F, C]
 * 			- FORMAT TEXTURE: [ID] [relative path to file] (sample: SO ./path_to_the_south_texture)
 * 			- FORMAT COLOR: [ID] [R,G,B] (sample: F 220,100,0)
 * 		- [] too many data (use flag)
 * 		- [] NO (north), SO (south), WE (west), EA (east) with path to texture file valid.
 * 				- files can be PNG or XPM convert to mlx_texture
 * 		- [] F (floor), C (ceiling) with color valid.
 * 				- convert to int.
 *
 * 	TODO: parsing map and set [[vars->m]] and [[vars.p]] (2D array, player position, player direction)
 * 		ERRORS to manage:
 * 			- [] map is not closed
 * 			- [] amount player different to 1
 * 			- [] player position is valid (N, S, E, W)
 *
 * 	DATA TO SET:
 * 	    - [[vars->a]]
 * 	    - [[vars->m]]
 * 	    - [[vars.p]]
 */


void	free_strrarr(char **to_free)
{
	int	i;

	i = 0;
	while (to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
}


void get_map_size(t_vars *vars, char **raw_file)
{
	int i;
	int j;

	i = 0;
	j = 0;
	vars->m.s.h = 0;
	vars->m.s.w = 0;

	while(raw_file[i])
	{
		j = 0;
		while(raw_file[i][j])
		{
			j++;
		}
		if ((int)vars->m.s.w < j)
			vars->m.s.w = j;
		i ++;
	}
	vars->m.s.h = i;
	// printf("Map width [%d] map height[%d]\n",vars->m.s.w, vars->m.s.h);
}

void allocate_map_array(t_vars *vars, char **raw_file)
{	
	int i;
	int x;
	int y;

	i = 0;
	x = 0;
	y = 0;
	vars->m.m = (int **)ft_calloc(1, sizeof(int *) * vars->m.s.h);
	while (i < (int)vars->m.s.h)
		vars->m.m[i++] = (int *)ft_calloc(1, sizeof(int) * vars->m.s.w);
	while (y < (int)vars->m.s.h)
	{
		x = 0;
		while (raw_file[y][x])	
		{
				vars->m.m[y][x] = raw_file[y][x];
			x++;
		}
		y++;
	}
	
	//print map in term
	// for(int i = 0; i < (int)vars->m.s.h; i++)
	// {
	// 	for(int j = 0;  j< (int)vars->m.s.w;j++)
	// 	{
	// 		printf("[%c]",vars->m.m[i][j]);
	// 	}
	// 	printf("\n");
	// }
	
}
void init_map(t_vars *vars, char **raw_file)
{
	get_map_size(vars, raw_file);
	allocate_map_array(vars, raw_file);
	// init minimap data
	vars->mm.size.w = vars->m.s.w * 16;
	vars->mm.size.h = vars->m.s.h * 16;
	vars->mm.pos.X = 16; // c'est quoi ça donc ? ah la posiiton de la mini map je crois !!
	vars->mm.pos.Y = 16;
	
	// from mock init
	vars->mm.ratio = PIXEL_SIZE / MM_PIXEL_SIZE;
	vars->p.mm_c.X = vars->p.c.X / vars->mm.ratio;
	vars->p.mm_c.Y = vars->p.c.Y / vars->mm.ratio;
	vars->p.fov = FOV;
	vars->p.fov_2 = vars->p.fov / 2.0;
}


/***************TED*****************/


bool	open_file(char *file, int *fd)
{
	*fd = open(file, O_RDONLY);
	if (*fd == -1)
		return (false);
	return (true);
}

typedef char* str;


#define BUFFER_SIZE 32

int get_next_line(int fd, char **line)
{
    int     i = 0;
    int     rd = 0;
    char    character;
    char     *buffer = malloc(10000);
    *line = malloc(10000);

    while ((rd = read(fd, &character, BUFFER_SIZE - BUFFER_SIZE + 1)) > 0)
    {
        buffer[i++] = character;
        if (character == '\n')
            break;
    }
    if ((!buffer[i - 1] && !rd) || rd == -1)
    {
        free(buffer);
        return (0);
    }
    buffer[i] =  '\0';
	ft_strlcpy(*line,buffer,ft_strlen(buffer));
	free(buffer);
    return (i);
}
/*
	take a color string as input and return an int
	//TODO correct the function so it returns the correct number
*/
int	get_color(char *color)
{
	int r, g, b;
	char **parts;
	printf("color [%s]\n", color);
	parts = ft_split(color + 2, ',');
	if (parts == NULL)
		return (-1);
	int i = 0;
	while(parts[i])
	{
		printf("parts[%d] = [%s]\n",i,parts[i]);
		i++;
	}
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	free_strrarr(parts);
	printf("r [%d] g [%d] b [%d]\n", r, g, b);
	return ((int)(r << 24) | (int)(g << 16) | (int)(b << 8) | (int)(0xFF << 0));
	return ((int)(r << 24) | (int)(g << 16) | (int)(b << 8) | (int)(0xFF << 0));
}

#define NORTH 0x1
#define SOUTH 0x2
#define WEST 0x4
#define EAST 0x8
#define FLOOR 0x10
#define CEILING 0x20
#define TOTAL 0x3F
bool	parsing_file_map(char *file, t_vars *vars)
{
	int fd;
	if (!open_file(file, &fd))
		return (false);
	//init textures in order to put the path into it
	vars->a.textures = (mlx_texture_t **)malloc(sizeof(mlx_texture_t *) * 4);

	char	flag = 0x0;
	str		line;
	line = NULL;
	// get the textures
	// when every tecture is found, flag will be equal to 0x3F 
	while (get_next_line(fd, &line) > 0 && flag != TOTAL)
	{
		// printf("This is line [%s]\n", line);
		if (ft_strncmp(line, "NO ", 3) == 0)
		{
			if (flag & NORTH)
				return (false);
			flag |= NORTH;
			vars->a.textures[NORTH] = mlx_load_png(line + 3);
			if (vars->a.textures[NORTH] == NULL)
				return (false);
		}
		else if (ft_strncmp(line, "SO ", 3) == 0)
		{
			if (flag & SOUTH)
				return (false);
			flag |= SOUTH;
			vars->a.textures[SOUTH] = mlx_load_png(line + 3);
			if (vars->a.textures[SOUTH] == NULL)
				return (false);
		}
		else if (ft_strncmp(line, "WE ", 3) == 0)
		{
			if (flag & WEST)
				return (false);
			flag |= WEST;
			vars->a.textures[WEST] = mlx_load_png(line + 3);
			if (vars->a.textures[WEST] == NULL)
				return (false);
		}
		else if (ft_strncmp(line, "EA ", 3) == 0)
		{
			if (flag & EAST)
				return (false); //TODO free line and textures
			flag |= EAST;
			vars->a.textures[EAST] = mlx_load_png(line + 3);
			if (vars->a.textures[EAST] == NULL)
				return (false);
		}
		else if (ft_strncmp(line, "C ", 2) == 0)
		{
			//TODO manage color
			// vars->a.ceiling = get_color(line);
			// printf("This is the ceiling color [%d]\n", vars->a.ceiling);
			vars->a.ceiling = WHITEH;
			flag |= CEILING;
		}
		else if (ft_strncmp(line, "F ", 2) == 0)
		{
			//manage color
			// vars->a.floor = get_color(line);
			// printf("This is the ceiling color [%d]\n", vars->a.ceiling);
			vars->a.floor = ARMYH;
			flag |= FLOOR;
		}
		free(line);
	}
	printf("All textures acquired\n");

	//map parsing into a temp buffer (Cuz I don't know the size of the map)
	bool player_found = false;
	int j = 0;
	char **buffer;
	buffer = ft_calloc(200, sizeof(char *));
	while (get_next_line(fd, &line) > 0)
	{
		int i;

		i = 0;
		//check for empty line
		if (!ft_strchr(line, 'N') || !ft_strchr(line, 'S') || !ft_strchr(line, 'E') || !ft_strchr(line, '0'|| !ft_strchr(line, '1')))
		{
			printf("Empty line found\n");
			return (EXIT_FAILURE);
		}
		//check if the player is in the map
		if (ft_strchr(line, 'N') || ft_strchr(line, 'S') || ft_strchr(line, 'E') || ft_strchr(line, 'W'))
		{
			if (player_found)
				return (false);
			player_found = true;
			//Set player position
			if (ft_strchr(line, 'N'))
			{
				vars->p.c.X = (double)(i - 1) * PIXEL_SIZE + PIXEL_SIZE / 2.0;
				vars->p.c.Y = (double)j * PIXEL_SIZE + PIXEL_SIZE / 2.0;
				vars->p.angle = 0.0;
			}
			else if (ft_strchr(line, 'S'))
			{
				vars->p.c.X = (double)(i - 1) * PIXEL_SIZE + PIXEL_SIZE / 2.0;
				vars->p.c.Y = (double)j * PIXEL_SIZE + PIXEL_SIZE / 2.0;
				vars->p.angle = 180.0;
			}
			else if (ft_strchr(line, 'E'))
			{
				vars->p.c.X = (double)(i - 1) * PIXEL_SIZE + PIXEL_SIZE / 2.0;
				vars->p.c.Y = (double)j * PIXEL_SIZE + PIXEL_SIZE / 2.0;
				vars->p.angle = 90.0;
			}
			else if (ft_strchr(line, 'W'))
			{
				vars->p.c.X = (double)(i - 1) * PIXEL_SIZE + PIXEL_SIZE / 2.0;
				vars->p.c.Y = (double)j * PIXEL_SIZE + PIXEL_SIZE / 2.0;
				vars->p.angle = 270.0;
			}
		}
		
		//import line into temp 2d array
		buffer[j] = ft_strdup(line);
		j++;
		free(line);
	}
	//init map with the map data
	init_map(vars, buffer);
	free_strrarr(buffer);
	return (true);
	// return (EXIT_SUCCESS);
	
}
