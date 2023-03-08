
#include "../../include/cub3D.h"

static void	set_player(t_vars *vars, double angle, t_vectorI p, char **line)
{
	if (vars->flag & F_PLAYER)
	{
		printf("Player already set\n");
		vars->flag |= F_ERROR;
		return ;
	}
	vars->flag |= F_PLAYER;
	vars->p.c.X = (double)p.X * PIXEL_SIZE + PIXEL_SIZE / 2.0;
	vars->p.c.Y = (double)p.Y * PIXEL_SIZE + PIXEL_SIZE / 2.0;
	vars->p.angle = angle;
	(*line)[p.X] = '0';
}

#define CHAR_VALID "01NSEW "

static bool	skip_empty_line(char **line, int fd)
{
	while (gnl(fd, line) > 0)
	{
		if (*line && ft_issetinstr(*line, CHAR_VALID))
			return (true);
	}
	printf("Line not valid found [%s]\n", *line);
	return (false);
}

static bool	parse_map_line(t_vars *vars, char *line)
{
	int	i;

	i = 0;
	while (line[i] && !(vars->flag & F_ERROR))
	{
		if (line[i] == 'N')
			set_player(vars, M_PI / 2, (t_vectorI){i, vars->m.s.h}, &line);
		else if (line[i] == 'S')
			set_player(vars, M_PI * 3 / 2, (t_vectorI){i, vars->m.s.h}, &line);
		else if (line[i] == 'E')
			set_player(vars, 0, (t_vectorI){i, vars->m.s.h}, &line);
		else if (line[i] == 'W')
			set_player(vars, M_PI, (t_vectorI){i, vars->m.s.h}, &line);
		else if (line[i] == ' ' || ft_ischarinstr(line[i], "01"))
			;
		else
		{
			printf("Line not valid found [%s]\n", line);
			return (false);
		}
		i++;
	}
	if ((int)vars->m.s.w < i)
		vars->m.s.w = (u_int32_t)i;
	return (true);
}

bool	parse_map(t_vars *vars, int fd, char ***buffer)
{
	char	*line;

	vars->m.s.h = 0;
	vars->m.s.w = 0;
	vars->flag = 0x0;
	if (!skip_empty_line(&line, fd))
		return (false);
	(*buffer)[vars->m.s.h] = ft_strdup(line);
	free_null(line);
	while (gnl(fd, &line) > 0)
	{
		vars->m.s.h++;
		if (!parse_map_line(vars, line))
			return (false);
		if (vars->flag & F_ERROR)
		{
			printf("Error while parsing map\n");
			return (false);
		}
		(*buffer)[vars->m.s.h] = ft_strdup(line);
		free_null(line);
	}
	vars->m.s.h++;
	return (true);
}
