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
		if (!ft_strchr2(line, 'N') && !ft_strchr2(line, 'S') && !ft_strchr2(line, 'E') && !ft_strchr2(line, '0'&& !ft_strchr2(line, '1')))
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