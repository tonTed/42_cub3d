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


int freetab_ret(char ***tab, int ret, char *msg)
{
	ft_freetabstr(tab);
	if (msg)
		printf("%s", msg);
	return (ret);
}
/**
 * @brief Parse the file map and fill the vars struct
 *
 * @param file	path to the file
 * @param vars	pointer to the global vars struct
 *
 * @return EXIT_SUCCESS if success, EXIT_FAILURE if error.
 *
 * @todo refactor false return and free buffer
 */
static bool	open_file(char *file, int *fd)
{
	char	**tmp;
	int		i;

	tmp = ft_split(file, '.');
	i = ft_strtablen(tmp);
	*fd = open(file, O_RDONLY);
	if (*fd == -1)
		return (freetab_ret(&tmp, false, "Error: Could not open file\n"));
	if (ft_strncmp(tmp[i - 1], "cub", 3) != 0 || ft_strlen(tmp[i - 1]) > 3)
		return (freetab_ret(&tmp, false, "Error: Invalid file extension\n"));
	ft_freetabstr(&tmp);
	return (true);
}

bool	parse_file(char *file, t_vars *vars)
{
	int		fd;
	char	**buffer;

	if (!open_file(file, &fd))
		return (false);
	if (!parse_textures(vars, fd))
		return (false);
	buffer = malloc(sizeof(char *));
	if (!parse_map(vars, fd, &buffer))
		return (freetab_ret(&buffer, EXIT_FAILURE, NULL));
	if (vars->flag & F_ERROR)
		return (freetab_ret(&buffer, EXIT_FAILURE, NULL));
	init_map(vars, buffer);
	ft_freetabstr(&buffer);
	if (is_map_closed(vars) == false)
	{
		return (clean_textures(vars, EXIT_FAILURE, "Map is not closed\n"));
	}
	return (EXIT_SUCCESS);
}
