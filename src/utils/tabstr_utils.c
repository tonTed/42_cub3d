//
// Created by Teddy BLANCO on 2023-03-08.
//

#include "../../include/cub3D.h"

void	add_line_tabstr(char ***tabstr, char *line)
{
	char	**new_tabstr;
	int		i;

	new_tabstr = (char **)malloc(sizeof(char *) * (ft_strtablen(*tabstr)
			+ 2));
	i = 0;
	while ((*tabstr)[i])
	{
		new_tabstr[i] = (*tabstr)[i];
		i++;
	}
	new_tabstr[i++] = line;
	new_tabstr[i] = NULL;
	free(*(tabstr));
	*(tabstr) = new_tabstr;
}