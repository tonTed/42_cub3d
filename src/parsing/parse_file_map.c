/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:03:33 by tonted            #+#    #+#             */
/*   Updated: 2023/02/22 21:44:37 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

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

char	*ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

// void	free_strrarr(char **to_free)
// {
// 	int	i;

// 	i = 0;
// 	while (to_free[i])
// 	{
// 		free(to_free[i]);
// 		i++;
// 	}
// 	free(to_free);
// }

bool all_texture_set(t_vars *vars)
{
	return (vars->m.north == true && vars->m.south == true && vars->m.east == true
		 && vars->m.west == true && vars->m.ceiling == true && vars->m.floor == true);
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

bool	set_texture(t_vars *vars, char ***raw_file)
{
	char *north,*south,*east,*west;
	init_map_assets(vars);
	while(*(*raw_file))
	{
		if (all_texture_set(vars))
		{
			printf("NO [%s]\nSO [%s]\nWE [%s]\nEA [%s]\nF [%D]\nC [%D]\n", north,south,west,east,vars->a.floor,vars->a.ceiling);
			return(true);
		}
		if (ft_strncmp(*(*raw_file), "NO ./", 4) == 0)
		{
			// vars->a.north_texture->path = ft_calloc(1, ft_strlen(*(*raw_file)) + 1);
			// ft_strcpy(vars->a.north_texture->path, *(*raw_file));
			// vars->a.north_texture->path = *(*raw_file);
			north = *(*raw_file);
			vars->m.north = true;
		}
		if (ft_strncmp(*(*raw_file), "SO ./", 5) == 0)
		{
			// vars->a.south_texture->path = *(*raw_file);
			south = *(*raw_file);
			vars->m.south = true;
		}
		if (ft_strncmp(*(*raw_file), "WE ./", 5) == 0)
		{
			// vars->a.west_texture->path = *(*raw_file);
			west = *(*raw_file);
			vars->m.west = true;
		}
		if (ft_strncmp(*(*raw_file), "EA ./", 5) == 0)
		{
			// vars->a.east_texture->path = *(*raw_file);
			east = *(*raw_file);
			vars->m.east = true;
		}
		if (ft_strncmp(*(*raw_file), "F ", 2) == 0)
		{
			// vars->a.floor = ft_atoi(*(*raw_file));
			// TODO find a way of getting the numbers in a logical way
			vars->a.floor = 100;
			vars->m.floor = true;
		}
		if (ft_strncmp(*(*raw_file), "C ", 2) == 0)
		{
			// vars->a.ceiling = ft_atoi(*(*raw_file));
			// TODO find a way of getting the numbers in a logical way
			vars->a.ceiling = 1000;
			vars->m.ceiling = true;
		}
		(*raw_file)++;
	}
	// printf("NO [%s]\nSO [%s]\nWE [%s]\nEA [%s]\nF [%D]\nC [%D]\n", vars->a.north_texture->path,vars->a.south_texture->path,vars->a.west_texture->path,vars->a.east_texture->path,vars->a.floor,vars->a.ceiling);
	return (false);
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
	vars->m.m = (int **)ft_calloc(1, sizeof(int *) * vars->m.s.h);
	int i = 0;
	while (i < (int)vars->m.s.h)
		vars->m.m[i++] = (int *)ft_calloc(1, sizeof(int) * vars->m.s.w);
	int x = 0;
	int y = 0;
	while (y < (int)vars->m.s.h)
	{
		x = 0;
		while (x < (int)vars->m.s.w)
		{
				vars->m.m[y][x] = raw_file[y][x];
			x++;
		}
		y++;
	}
	for(int i = 0; i < (int)vars->m.s.h; i++)
	{
		for(int j = 0; j < (int)vars->m.s.w;j++)
		{
			printf("[%c]",vars->m.m[i][j]);
		}
		printf("\n");
	}
	
}
void init_map(t_vars *vars, char **raw_file)
{
	get_map_size(vars, raw_file);
	allocate_map_array(vars, raw_file);


}

bool	parsing_file_map2(char *file, t_vars *vars)
{
    WHOAMI
	int ret;
	char *buffer = malloc(sizeof(char) * 40000);
	char **tmp;
	char **raw_file;
	// open the map and put it into an array
	int fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	ret = read(fd, buffer, 40000);
	if (buffer == NULL)
	{
		perror("read");
		return (1);
	}
	raw_file = ft_split(buffer,'\n');
	free(buffer);
	tmp = raw_file;
	//get all the texture path - advance the pointer but stop before the map
	printf("Before you send to set_texture your pointer is at [%s]\n", *raw_file);
	if (set_texture(vars, &raw_file))
	{
		printf("YOU CAN NOW START TO LOOK FOR THE MAP your pointer is at [%s]\nHere is vars->a.ceiling [%d]\nHere is vars->a.floor [%d]\n", *raw_file,vars->a.ceiling,vars->a.floor);
		init_map(vars, raw_file);
	}

	// free_strrarr(tmp);
	(void)tmp;
	(void)ret;
	return (EXIT_SUCCESS);
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
	// read file line by line
	char	flag = 0x0;
	str		line;
	line = NULL;
	// while as long as the line is not empty and we haven't found all the textures/floor/ceiling
	while (get_next_line(fd, &line) > 0 && flag != TOTAL)
	{
		printf("This is line [%s]\n", line);
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
				return (false);
			flag |= EAST;
			vars->a.textures[EAST] = mlx_load_png(line + 3);
			if (vars->a.textures[EAST] == NULL)
				return (false);
		}
		else if (ft_strncmp(line, "C ", 2) == 0)
		{
			//manage color
			flag |= FLOOR;
		}
		else if (ft_strncmp(line, "F ", 2) == 0)
		{
			//manage color
			flag |= CEILING;
		}
		free(line);
	}

	while (get_next_line(fd, &line) > 0)
	{
		//manage map

	}
	return (true);
}
