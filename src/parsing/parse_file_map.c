/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:03:33 by tonted            #+#    #+#             */
/*   Updated: 2023/03/06 14:52:15 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"
#include <stdbool.h>

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

char    *ft_strcpy(char *s1, char *s2)
{
      int i;
 
      i = 0;
      while (s2[i])
      {
          s1[i] = s2[i]; 
          i++;
      }
      s1[i] = s2[i];
      return (s1);
}

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


void	init_map_assets(t_vars *vars)
{
	vars->m.east = false;
	vars->m.west = false;
	vars->m.north = false;
	vars->m.south = false;
	vars->m.floor = false;
	vars->m.ceiling = false;
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
		j = ft_strlen(raw_file[i]);
		if ((int)vars->m.s.w < j)
			vars->m.s.w = j;
		i ++;
	}
	vars->m.s.h = i;
}

void	print_map(t_vars *vars)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < (int)vars->m.s.h)
	{
		j = 0;
		while (j < (int)vars->m.s.w)
		{
			printf("[%d]", vars->m.m[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
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
	print_map(vars);
}

void init_map(t_vars *vars, char **raw_file)
{
	get_map_size(vars, raw_file);
	allocate_map_array(vars, raw_file);
	vars->mm.size.w = vars->m.s.w * MM_PIXEL_SIZE;
	vars->mm.size.h = vars->m.s.h * MM_PIXEL_SIZE;
	vars->mm.pos.X = 16;
	vars->mm.pos.Y = 16;
	vars->mm.ratio = PIXEL_SIZE / MM_PIXEL_SIZE;
	vars->p.mm_c.X = vars->p.c.X / vars->mm.ratio;
	vars->p.mm_c.Y = vars->p.c.Y / vars->mm.ratio;
	vars->p.fov = FOV;
	vars->p.fov_2 = vars->p.fov / 2.0;
}


/***************TED*****************/

/*
	Check if the file has a valid map extension

*/
int		ft_strarrlen(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

bool	open_file(char *file, int *fd)
{
	char **tmp;
	int i;

	tmp = ft_split(file, '.');
	i = ft_strarrlen(tmp);
	*fd = open(file, O_RDONLY);
	if (*fd == -1)
	{
		printf("Error\nCould not open file\n");
		free_strrarr(tmp);
		return (false);
	}
	if (ft_strncmp(tmp[i-1], "cub", 3) != 0  || ft_strlen(tmp[i-1]) > 3)
	{
		printf("Error\nInvalid file extension\n");
		free_strrarr(tmp);
		return (false);
	}
	free_strrarr(tmp);
	return (true);
}

typedef char* str;


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

/*
	This function first call open file which will check if the file has a valid extension and if it can be opened
*/

bool	evaluate_texture(char *flag, t_vars *vars, char *line, int f_value, int value)
{
	if (*flag & f_value)
		return (false);
	*flag |= f_value;
	vars->a.textures[value] = mlx_load_png(line + 3);
	if (vars->a.textures[value] == NULL)
		return (false);
	return (true);
}

bool	get_texture(t_vars *vars, str line, int fd)
{
	char	flag = 0x0;
	vars->a.textures = (mlx_texture_t **)malloc(sizeof(mlx_texture_t *) * 4);
	while (gnl(fd, &line) > 0 && flag != TOTAL)
	{
		if (!line)
			continue ;
		if (!ft_strncmp(line, "NO ", 3))
			evaluate_texture(&flag, vars, line, F_NORTH, NORTH);
		else if (ft_strncmp(line, "SO ", 3) == 0)
			evaluate_texture(&flag, vars, line, F_SOUTH, SOUTH);
		else if (ft_strncmp(line, "WE ", 3) == 0)
			evaluate_texture(&flag, vars, line, F_WEST, WEST);
		else if (ft_strncmp(line, "EA ", 3) == 0)
			evaluate_texture(&flag, vars, line, F_EAST, EAST);
		else if (ft_strncmp(line, "C ", 2) == 0)
		{
			vars->a.ceiling = get_color(line);
			flag |= CEILING;
		}
		else if (ft_strncmp(line, "F ", 2) == 0)
		{
			vars->a.floor = get_color(line);
			flag |= FLOOR;
		}
		free_null(line);
	}
	return (true);
	printf("All textures acquired\n");
}


bool	get_map(t_vars *vars, int fd, str line, char ***buffer, bool *player_found)
{
	int j;
	int i;

	j = 0;
	while (gnl(fd, &line) > 0)
	{
		i = 0;
		if (!ft_strchr(line, 'N') && !ft_strchr(line, 'S') && !ft_strchr(line, 'E') && !ft_strchr(line, '0'&& !ft_strchr(line, '1')))
		{
			printf("Empty line found [%s]\n",line);
			return (false);
		}
		while(line[i] && *player_found == false)
		{
			if (line[i] == 'S' || line[i] == 'N' || line[i] == 'E' || line[i] == 'W')
			{
				*player_found = true;
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
		(*buffer)[j] = ft_strdup(line);
		j++;
		free_null(line);
	}
	return (true);
}

bool	parsing_file_map(char *file, t_vars *vars)
{
	int fd;
	str		line;
	char **buffer;
	bool player_found = false;

	line = NULL;
	player_found = false;
	if (!open_file(file, &fd))
		return (false);
	vars->a.textures = (mlx_texture_t **)malloc(sizeof(mlx_texture_t *) * 4);
	if (get_texture(vars, line,  fd) == false)
		return false;
	buffer = ft_calloc(200, sizeof(char *));
	if (get_map(vars, fd, line, &buffer, &player_found) == false)
		return (EXIT_FAILURE);
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
}
