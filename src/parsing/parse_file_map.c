/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:03:33 by tonted            #+#    #+#             */
/*   Updated: 2023/03/01 17:36:36 by pirichar         ###   ########.fr       */
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
	printf("Map width [%d] map height[%d]\n",vars->m.s.w, vars->m.s.h);
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
				vars->m.m[y][x] = raw_file[y][x] - '0';
			x++;
		}
		y++;
	}
	// print map in term
	for(int i = 0; i < (int)vars->m.s.h; i++)
	{
		for(int j = 0;  j< (int)vars->m.s.w;j++)
		{
			printf("[%d]",vars->m.m[i][j]);
		}
		printf("\n");
	}
	
}
void init_map(t_vars *vars, char **raw_file)
{
	get_map_size(vars, raw_file);
	allocate_map_array(vars, raw_file);
	// init minimap data
	vars->mm.size.w = vars->m.s.w * 16;
	vars->mm.size.h = vars->m.s.h * 16;
	vars->mm.pos.X = 16; 
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

int	gnl(int fd, char **line)
{
	int br;
	char buffer[2];
	char *tmp = NULL;

	buffer[1] = '\0';
	*line = NULL;
	while (42)
	{
		br = read(fd, &buffer, 1);
		if (br == -1)
			return (-1);
		if (br == 0)
		{
			if (*line == NULL)
				return (0);
			else
				return (1);
		}
		if (buffer[0] == '\n')
			return (1);
		if (*line == NULL)
			*line = ft_strdup(buffer);
		else
		{
			tmp = *line;
			*line = ft_strjoin(*line, buffer);
			free_null(tmp);
		}
	}
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

#define F_NORTH 0x1
#define F_SOUTH 0x2
#define F_WEST 0x4
#define F_EAST 0x8
#define FLOOR 0x10
#define CEILING 0x20
#define TOTAL 0x3F

unsigned int rgb_to_int(char* color_str) {
    char **tok;
    unsigned int color_int = 0;
    int i = 0;

    tok = ft_split(color_str, ',');
    while (tok[i]) {
        int color_val = ft_atoi(*tok);
        if (color_val > 255 || color_val < 0) {
            printf("Error: color value out of range (0-255)\n");
            return 0;
        }
        color_int |= (color_val << (8 * i));
        i++;
    }

    return color_int;
}


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
	while (gnl(fd, &line) > 0 && flag != TOTAL)
	{
		if (!line)
			continue ;
		if (!ft_strncmp(line, "NO ", 3))
		{
			if (flag & F_NORTH)
				return (false);
			flag |= F_NORTH;
			vars->a.textures[NORTH] = mlx_load_png(line + 3);
			if (vars->a.textures[NORTH] == NULL)
				return (false);
		}
		else if (ft_strncmp(line, "SO ", 3) == 0)
		{
			if (flag & F_SOUTH)
				return (false);
			flag |= F_SOUTH;
			vars->a.textures[SOUTH] = mlx_load_png(line + 3);
			if (vars->a.textures[SOUTH] == NULL)
				return (false);
		}
		else if (ft_strncmp(line, "WE ", 3) == 0)
		{
			if (flag & F_WEST)
				return (false);
			flag |= F_WEST;
			vars->a.textures[WEST] = mlx_load_png(line + 3);
			if (vars->a.textures[WEST] == NULL)
				return (false);
		}
		else if (ft_strncmp(line, "EA ", 3) == 0)
		{
			if (flag & F_EAST)
				return (false); //TODO free line and textures
			flag |= F_EAST;
			vars->a.textures[EAST] = mlx_load_png(line + 3);
			if (vars->a.textures[EAST] == NULL)
				return (false);
		}
		else if (ft_strncmp(line, "C ", 2) == 0)
		{
			//TODO manage color
			vars->a.ceiling = get_color(line);
			printf("This is the ceiling color [%d]\n", vars->a.ceiling);
			// vars->a.ceiling = WHITEH;
			flag |= CEILING;
		}
		else if (ft_strncmp(line, "F ", 2) == 0)
		{
			//manage color
			vars->a.floor = get_color(line);
			printf("This is the ceiling color [%d]\n", vars->a.ceiling);
			// vars->a.floor = ARMYH;
			flag |= FLOOR;
		}
//		free_null(line);
	}
	printf("All textures acquired\n");

	//map parsing into a temp buffer (Cuz I don't know the size of the map)
	bool player_found = false;
	int j = 0;
	char **buffer;
	buffer = ft_calloc(200, sizeof(char *));
	while (gnl(fd, &line) > 0)
	{
		int i = 0;
		//check for empty line
		if (!ft_strchr(line, 'N') && !ft_strchr(line, 'S') && !ft_strchr(line, 'E') && !ft_strchr(line, '0'&& !ft_strchr(line, '1')))
		{
			printf("Empty line found [%s]\n",line);
			return (EXIT_FAILURE);
		}
		//check if the player is in the map
		while(line[i] && player_found == false)
		{
			if (line[i] == 'S' || line[i] == 'N' || line[i] == 'E' || line[i] == 'W')
			{
				player_found = true;
				//Set player position
				if (line[i] == 'N')
				{
					printf("Found a player facing north\n");
					vars->p.c.X = i * PIXEL_SIZE + PIXEL_SIZE / 2.0;
					vars->p.c.Y = j * PIXEL_SIZE + PIXEL_SIZE / 2.0;
					vars->p.angle = M_PI / 2;
				}
				else if (line[i] == 'S')
				{
					printf("Found a player facing south\n");
					vars->p.c.X = (double)i * PIXEL_SIZE + PIXEL_SIZE / 2.0;
					vars->p.c.Y = (double)j * PIXEL_SIZE + PIXEL_SIZE / 2.0;
					vars->p.angle = M_PI * 3 / 2;
				}
				else if (line[i] == 'E')
				{
					printf("Found a player facing east\n");
					vars->p.c.X = (double)i* PIXEL_SIZE + PIXEL_SIZE / 2.0;
					vars->p.c.Y = (double)j * PIXEL_SIZE + PIXEL_SIZE / 2.0;
					vars->p.angle = 0.0;
				}
				else if (line[i] == 'W')
				{
					printf("Found a player facing west\n");
					vars->p.c.X = (double)i* PIXEL_SIZE + PIXEL_SIZE / 2.0;
					vars->p.c.Y = (double)j * PIXEL_SIZE + PIXEL_SIZE / 2.0;
					vars->p.angle = M_PI;
				}
				line[i] = '0';
			}
			i++;
		}
		//import line into temp 2d array
		buffer[j] = ft_strdup(line);
		j++;
		free_null(line);
	}
	//init map with the map data
	if (player_found)
	{
		printf("This is player position [%f][%f]\n", vars->p.c.X, vars->p.c.Y);
		init_map(vars, buffer);
		free_strrarr(buffer);
		return (EXIT_SUCCESS);	
	}
	else 
	{
		printf("no player found\n");
		return(EXIT_FAILURE);
	}
	// return (true);
	
}
