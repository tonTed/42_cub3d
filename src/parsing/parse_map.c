//
// Created by Teddy BLANCO on 2023-03-06.
//

#include "../../include/cub3D.h"

void	set_player(t_vars *vars, int i, int j, double angle)
{
	vars->p.c.X = (double)i * PIXEL_SIZE + PIXEL_SIZE / 2.0;
	vars->p.c.Y = (double)j * PIXEL_SIZE + PIXEL_SIZE / 2.0;
	vars->p.angle = angle;
	vars->flag = 0x0;
}

bool	parse_map(t_vars *vars, int fd, char ***buffer)
{
	int j;
	int i;
	char *line;

	j = 0;
	vars->flag = F_ERROR;
	while (gnl(fd, &line) > 0)
	{
		i = 0;
		if (!ft_strchr(line, 'N') && !ft_strchr(line, 'S') && !ft_strchr(line, 'E') && !ft_strchr(line, '0'&& !ft_strchr(line, '1')))
		{
			printf("Empty line found [%s]\n",line);
			return (false);
		}
		while(line[i] && vars->flag)
		{
			if (line[i] == 'S' || line[i] == 'N' || line[i] == 'E' || line[i] == 'W')
			{
				vars->flag = 0x0;
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