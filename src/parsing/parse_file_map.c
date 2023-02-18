/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:03:33 by tonted            #+#    #+#             */
/*   Updated: 2023/02/18 02:02:57 by pirichar         ###   ########.fr       */
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

bool	set_texture(t_vars *vars, char ***raw_file)
{
	char *north,*south,*east,*west;
	vars->m.east = false;
	vars->m.west = false;
	vars->m.north = false;
	vars->m.south = false;
	vars->m.floor = false;
	vars->m.ceiling = false;
	int i = 0;
	while(*(*raw_file))
	{
		if (vars->m.north == true && vars->m.south == true && vars->m.east == true && vars->m.west == true && vars->m.ceiling == true && vars->m.floor == true)
			return(true);
		// printf("Parsing print - %s\n",*(*raw_file));
		if (ft_strncmp(*(*raw_file), "NO ./", 4) == 0)
		{
			// vars->a.north_texture->path = *(*raw_file);
			north = *(*raw_file);
			printf("north path set\n");
			vars->m.north = true;
		}
		if (ft_strncmp(*(*raw_file), "SO ./", 5) == 0)
		{
			// vars->a.south_texture->path = *(*raw_file);
			south = *(*raw_file);
			printf("South path set\n");
			vars->m.south = true;
		}
		if (ft_strncmp(*(*raw_file), "WE ./", 5) == 0)
		{
			// vars->a.west_texture->path = *(*raw_file);
			west = *(*raw_file);
			printf("West path set\n");
			vars->m.west = true;
		}
		if (ft_strncmp(*(*raw_file), "EA ./", 5) == 0)
		{
			// vars->a.east_texture->path = *(*raw_file);
			east = *(*raw_file);
			printf("East path set\n");
			vars->m.east = true;
		}
		if (ft_strncmp(*(*raw_file), "F ", 2) == 0)
		{
			// vars->a.floor = ft_atoi(*(*raw_file));
			// TODO find a way of getting the numbers in a logical way
			vars->a.floor = 100;
			printf("Floor color set\n");
			vars->m.floor = true;
		}
		if (ft_strncmp(*(*raw_file), "C ", 2) == 0)
		{
			// vars->a.ceiling = ft_atoi(*(*raw_file));
			// TODO find a way of getting the numbers in a logical way
			vars->a.ceiling = 1000;
			printf("Ceiling color set\n");
			vars->m.ceiling = true;
		}
		(*raw_file)++;
		i++;
	}
	// printf("NO [%s]\nSO [%s]\nWE [%s]\nEA [%s]\nF [%D]\nC [%D]\n", vars->a.north_texture->path,vars->a.south_texture->path,vars->a.west_texture->path,vars->a.east_texture->path,vars->a.floor,vars->a.ceiling);
	// printf("NO [%s]\nSO [%s]\nWE [%s]\nEA [%s]\nF [%D]\nC [%D]\n", north,south,west,east,vars->a.floor,vars->a.ceiling);
	return (false);
}


bool	parsing_file_map(char *file, t_vars *vars)
{
    WHOAMI
	int ret;
	char *buffer = malloc(sizeof(char) * 4000);
	char **tmp;
	char **raw_file;
	// open the map and put it into an array
	printf("Path to file = [%s]\n", file);
	int fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	printf("fd = [%d]\n",fd);
	ret = read(fd, buffer, 4000);
	printf("This is ret [%d]\n",ret);
	if (buffer == NULL)
	{
		perror("read");
		return (1);
	}
	// printf("This is buffer = [%s]\n",buffer);
	//split the array into an array of strings
	raw_file = ft_split(buffer,'\n');
	free(buffer);
	tmp = raw_file;
	//get all the texture path - advance the pointer but stop before the map
	if (set_texture(vars, &raw_file))
		printf("YOU CAN NOW START TO LOOK FOR THE MAP your pointer is at %s\n", *raw_file);
	//get map height and width
	//malloc the vars
	// int i = 0;
	// while (i < vars->m.s.h)
	// 	vars->m.m[i++] = (int *)malloc(sizeof(int) * vars->m.s.w);
	// int x = 0;
	// int y = 0;
	// char **rtn = ft_split(file,'\n');
	// while (y < vars->m.s.h)
	// {
	// 	x = 0;
	// 	while (x < vars->m.s.w)
	// 	{
	// 		vars->m.m[y][x] = rtn[y][x];
	// 		x++;
	// 	}
	// 	y++;
	// }

	// free_strrarr(tmp);
	return (EXIT_SUCCESS);
}
