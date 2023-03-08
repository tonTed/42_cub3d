/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:06:54 by tonted            #+#    #+#             */
/*   Updated: 2023/03/08 10:08:22 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/**
 * @brief Parse the textures, set the flag and load the textures.
 *
 * @param vars	pointer to the main structure
 * @param line	line to parse
 */
static void	set_texture(t_vars *vars, char *line, int f_value, int value)
{
	if (vars->flag & f_value)
	{
		printf("Error: Duplicate texture. (%s)\n", line);
		vars->flag |= F_ERROR;
	}
	vars->flag |= f_value;
	vars->a.textures[value] = mlx_load_png(line + 2);
	if (vars->a.textures[value] == NULL)
	{
		printf("Error: Failed to load texture. (%s)\n", line);
		vars->flag |= F_ERROR;
	}
}

/**
 * @brief Parse the colors, set the flag and set the colors.
 *
 * @param vars	pointer to the main structure
 * @param line	line to parse
 */
static void	set_color(char *color, t_vars *vars, int f_value, int value)
{
	int		rgb[3];
	int		i;
	char	**parts;

	parts = ft_split(color + 1, ',');
	if (vars->flag & f_value || parts == NULL || ft_strtablen(parts) != 3)
	{
		printf("Error.\nDuplicate color or invalid color. (%s)\n", color);
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
		{
			printf("Error.\nInvalid color. (%s)\n", color);
			vars->flag |= F_ERROR;
		}
		i++;
	}
	vars->flag |= f_value;
	vars->a.colors[value] = ((int)(rgb[0] << 24) | (int)(rgb[1] << 16)
			| (int)(rgb[2] << 8) | (int)(0xFF << 0));
}

static bool	init_textures(t_vars *vars)
{
	vars->a.textures = (mlx_texture_t **)malloc(sizeof(mlx_texture_t *) * 4);
	if (vars->a.textures == NULL)
	{
		printf("Error\nMalloc failed (%s).\n", __func__);
		return (false);
	}
	vars->a.textures[NORTH] = NULL;
	vars->a.textures[SOUTH] = NULL;
	vars->a.textures[WEST] = NULL;
	vars->a.textures[EAST] = NULL;
	return (true);
}

/**
 * @brief Parse the textures and colors.
 *
 * @param vars	pointer to the main structure
 * @param fd	file descriptor
 *
 * @return true if the parsing is successful
 * @return false if the parsing failed
 *
 */
bool	parse_textures(t_vars *vars, int fd)
{
	char	*line;

	if (!init_textures(vars))
		return (false);
	while (vars->flag != TOTAL && gnl(fd, &line) > 0)
	{
		if (!line)
			continue ;
		remove_spaces(&line);
		if (!ft_strncmp(line, "NO", 2))
			set_texture(vars, line, F_NORTH, NORTH);
		else if (ft_strncmp(line, "SO", 2) == 0)
			set_texture(vars, line, F_SOUTH, SOUTH);
		else if (ft_strncmp(line, "WE", 2) == 0)
			set_texture(vars, line, F_WEST, WEST);
		else if (ft_strncmp(line, "EA", 2) == 0)
			set_texture(vars, line, F_EAST, EAST);
		else if (ft_strncmp(line, "C", 1) == 0 && ft_isdigit(line[1]))
			set_color(line, vars, F_CEILING, CEILING);
		else if (ft_strncmp(line, "F", 1) == 0 && ft_isdigit(line[1]))
			set_color(line, vars, F_FLOOR, FLOOR);
		free_null(line);
	}
	if (vars->flag != TOTAL)
		return (clean_textures(vars, false, "Error: Parsing texture.\n"));
	return (true);
}
