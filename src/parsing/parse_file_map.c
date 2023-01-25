/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:03:33 by tonted            #+#    #+#             */
/*   Updated: 2023/01/17 11:03:37 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/**
 * This functions open map file, parse it and set the different parameters of
 * vars.
 *
 * @param file relative path to the map file
 * @param vars global structure of the project
 * @return Non-negative if error occurred while the parsing
 */
int32_t parsing_file_map(char *file, t_vars *vars)
{
	WHOAMI
	//TODO Open file and manage errors

	/* TODO parse assets description
	 * Get every line and parse it:
	 * 		path to texture:
	 * 			- [ID] [relative path to file] (sample: SO ./path_to_the_south_texture)
	 * 			- ID valid: NO (north), SO (south), WE (west), EA (east)
	 * 			- set vars->assets.(...)_texture.
	 * 		colors:
	 * 			- [ID] [R,G,B] (sample: F 220,100,0)
	 * 			- ID valid: F (floor), C (ceiling)
	 * 			- set vars->assets.floor/ceiling
	 * 	Errors to manage:
	 * 		- [] missing data (use flag)
	 * 		- [] too many data (use flag)
	 * 		- [] file can't be open
	 * 		-
	 * */

	/* TODO parse map
	 *
	 * */

	(void)file;
	(void)vars;

	return (EXIT_SUCCESS);
}