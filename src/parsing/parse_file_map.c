/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:03:33 by tonted            #+#    #+#             */
/*   Updated: 2023/03/06 23:28:59 by pirichar         ###   ########.fr       */
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

void	get_map_size(t_vars *vars, char **raw_file)
{
	int	i;
	int	j;

	i = 0;
	vars->m.s.h = 0;
	vars->m.s.w = 0;
	while (raw_file[i])
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
	int	i;
	int	j;

	i = 0;
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

void	allocate_map_array(t_vars *vars, char **raw_file)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	y = 0;
	vars->m.m = (int **)ft_calloc(1, sizeof(int *) * vars->m.s.h);
	while (i < (int)vars->m.s.h)
		vars->m.m[i++] = (int *)ft_calloc(1, sizeof(int) * vars->m.s.w);
	while (y < (int)vars->m.s.h)
	{
		x = 0;
		while (x < (int)vars->m.s.w && raw_file[y][x])
		{
			vars->m.m[y][x] = raw_file[y][x] - '0';
			x++;
		}
		while (x < (int)vars->m.s.w)
			vars->m.m[y][x++] = -16;
		y++;
	}
	print_map(vars);
}

void	init_map(t_vars *vars, char **raw_file)
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

int	ft_strarrlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

bool	open_file(char *file, int *fd)
{
	char	**tmp;
	int		i;

	tmp = ft_split(file, '.');
	i = ft_strarrlen(tmp);
	*fd = open(file, O_RDONLY);
	if (*fd == -1)
	{
		printf("Error\nCould not open file\n");
		ft_freetabstr(&tmp);
		return (false);
	}
	if (ft_strncmp(tmp[i - 1], "cub", 3) != 0 || ft_strlen(tmp[i - 1]) > 3)
	{
		printf("Error\nInvalid file extension\n");
		ft_freetabstr(&tmp);
		return (false);
	}
	ft_freetabstr(&tmp);
	return (true);
}

int	gnl(int fd, char **line)
{
	int		br;
	char	buffer[2];
	char	*tmp;

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

#define F_NORTH 0x1 // 0000 0001
#define F_SOUTH 0x2 // 0000 0010
#define F_WEST 0x4 // 0000 0100
#define F_EAST 0x8 // 0000 1000
#define F_FLOOR 0x10 // 0001 0000
#define F_CEILING 0x20 // 0010 0000
#define F_ERROR 0x40 // 0100 0000
#define TOTAL 0x3F // 0011 1111
/*
	take a color string as input and return an int
*/
void	get_color(char *color, t_vars *vars, int f_value, int value)
{
	int 	rgb[3];
	char	**parts;
	int 	i;

	parts = ft_split(color + 2, ',');
	if (vars->flag & f_value || parts == NULL || ft_strarrlen(parts) != 3)
	{
		vars->flag |= F_ERROR;
		return ;
	}
	rgb[0] = ft_atoi(parts[0]);
	rgb[1] = ft_atoi(parts[1]);
	rgb[2] = ft_atoi(parts[2]);
	ft_freetabstr(&parts);
	i = 0;
	while (i < 3)
	{
		if ((rgb[i] < 0 || rgb[i] > 255))
			vars->flag |= F_ERROR;
		i++;
	}
	vars->flag |= f_value;
	vars->a.colors[value] = ((int)(rgb[0] << 24) | (int)(rgb[1] << 16)
			| (int)(rgb[2] << 8) | (int)(0xFF << 0));
}



/**
 * @brief This function will check if the file has a valid extension and if it can be opened
 *
 * @param file
 * @param fd	pointer to the file descriptor
 * @return true
 */
void	evaluate_texture(t_vars *vars, char *line, int f_value, int value)
{
	if (vars->flag & f_value)
		vars->flag |= F_ERROR;
	vars->flag |= f_value;
	vars->a.textures[value] = mlx_load_png(line + 3);
	if (vars->a.textures[value] == NULL)
		vars->flag |= F_ERROR;
}

bool	get_texture(t_vars *vars, char *line, int fd)
{
	vars->flag = 0x0;
	vars->a.textures = (mlx_texture_t **)malloc(sizeof(mlx_texture_t *) * 4);
	while (gnl(fd, &line) > 0 && vars->flag != TOTAL)
	{
		if (!line)
			continue ;
		if (!ft_strncmp(line, "NO ", 3))
			evaluate_texture(vars, line, F_NORTH, NORTH);
		else if (ft_strncmp(line, "SO ", 3) == 0)
			evaluate_texture(vars, line, F_SOUTH, SOUTH);
		else if (ft_strncmp(line, "WE ", 3) == 0)
			evaluate_texture(vars, line, F_WEST, WEST);
		else if (ft_strncmp(line, "EA ", 3) == 0)
			evaluate_texture(vars, line, F_EAST, EAST);
		else if (ft_strncmp(line, "C ", 2) == 0)
			get_color(line, vars, F_CEILING, CEILING);
		else if (ft_strncmp(line, "F ", 2) == 0)
			get_color(line, vars, F_FLOOR, FLOOR);
		free_null(line);
	}
	if (vars->flag != TOTAL)
		return (false);
	return (true);
}

void	set_player(t_vars *vars, int i, int j, double angle)
{
	vars->p.c.X = (double)i * PIXEL_SIZE + PIXEL_SIZE / 2.0;
	vars->p.c.Y = (double)j * PIXEL_SIZE + PIXEL_SIZE / 2.0;
	vars->p.angle = angle;
	vars->flag = 0x0;
}


bool is_map_closed(t_vars *vars) {

    // Check if the first and last rows are closed by 1's or spaces
    for (unsigned int i = 0; i < vars->m.s.w; i++) {
        if ((vars->m.m[0][i] != 1 && vars->m.m[0][i] != -16 )|| (vars->m.m[vars->m.s.h-1][i] != 1 && vars->m.m[vars->m.s.h-1][i] != -16)) {
            return false;
        }
    }

    // Check if the first and last columns (excluding corners) are closed by 1's or spaces
    for (unsigned int i = 1; i < vars->m.s.h-1; i++) {
        if ((vars->m.m[i][0] != 1 && vars->m.m[i][0] != -16 )||( vars->m.m[i][vars->m.s.w-1] != 1 && vars->m.m[i][vars->m.s.w-1] != -16)) {
            return false;
        }
    }

    // Check if there are any spaces adjacent to a 0
    for (unsigned int i = 1; i < vars->m.s.h-1; i++) {
        for (unsigned int j = 1; j < vars->m.s.w-1; j++) {
            if (vars->m.m[i][j] == 0) {
                if ((vars->m.m[i-1][j] == -16 || vars->m.m[i+1][j] == -16) || (vars->m.m[i][j-1] == -16 || vars->m.m[i][j+1] == -16)) {
                    return false;
                }
            }
        }
    }

    // If all checks pass, then the map is closed
    return true;
}

char	*ft_strchr2(const char *s, int c)
{
	int	i;

	if (s)
	{
		i = ft_strlen(s) + 1;
		while (--i >= 0)
			if (s[i] == (char) c)
				return ((char *) &s[i]);
	}
	return (NULL);
}


bool	get_map(t_vars *vars, int fd, char *line, char ***buffer, bool *player_found)
{
	int j;
	int i;

	j = 0;
	vars->flag = F_ERROR;
	while (gnl(fd, &line) > 0)
	{
		i = 0;
		if (!ft_strchr2(line, 'N') && !ft_strchr2(line, 'S') && !ft_strchr2(line, 'E') && !ft_strchr2(line, '0'&& !ft_strchr2(line, '1')))
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
					set_player(vars, i, j, M_PI / 2);
				else if (line[i] == 'S')
					set_player(vars, i, j, M_PI * 3 / 2);
				else if (line[i] == 'E')
					set_player(vars, i, j, 0);
				else if (line[i] == 'W')
					set_player(vars, i, j, M_PI);
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
	int 	fd;
	char	*line;
	char 	**buffer;
	bool 	player_found;

	line = NULL;
	player_found = false;
	if (!open_file(file, &fd))
		return (EXIT_FAILURE);
	vars->a.textures = (mlx_texture_t **)malloc(sizeof(mlx_texture_t *) * 4);
	if (get_texture(vars, line,  fd) == false)
	{
		printf("Error while parsing texture\n");
		return(EXIT_FAILURE);
	}
	buffer = ft_calloc(200, sizeof(char *));
	if (get_map(vars, fd, line, &buffer, &player_found) == false)
		return (EXIT_FAILURE);
	if (player_found)
	{
		printf("This is player position [%f][%f]\n", vars->p.c.X, vars->p.c.Y);
		init_map(vars, buffer);
		ft_freetabstr(&buffer);
		if (is_map_closed(vars) == false) {
			printf("Map is not closed\n");
			return (EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
	else
	{
		printf("no player found\n");
		return(EXIT_FAILURE);
	}
}
