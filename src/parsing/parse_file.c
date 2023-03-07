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

bool	open_file(char *file, int *fd)
{
	char	**tmp;
	int		i;

	tmp = ft_split(file, '.');
	i = ft_strtablen(tmp);
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

bool	parse_file(char *file, t_vars *vars)
{
	int 	fd;
	char 	**buffer;

	if (!open_file(file, &fd))
		return (false);
	if (!parse_textures(vars, fd))
	{
		printf("Error while parsing texture\n");
		return (false);
	}
	buffer = ft_calloc(200, sizeof(char *));
	if (!parse_map(vars, fd, &buffer))
	{
		printf("Error while parsing map\n");
		return (false);
	}
	if (!(vars->flag & F_ERROR))
	{
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
