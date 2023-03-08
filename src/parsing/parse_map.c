/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:06:38 by tonted            #+#    #+#             */
/*   Updated: 2023/03/08 10:06:43 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	set_player(t_vars *vars, double angle, t_vectorI p, char **line)
{
	if (vars->flag & F_PLAYER)
	{
		printf("Error: Player already set\n");
		free_null(*line);
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

static bool	skip_empty_line(char **line, int fd, char *set)
{
	while (gnl(fd, line) > 0)
	{
		if (*line && ft_issetinstr(*line, set))
			return (true);
	}
	printf("Error: Line not valid found [%s]\n", *line);
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

bool	manage_lines_after_map(char **line, int fd, char *set)
{
	int	br;

	while (42)
	{
		br = gnl(fd, line);
		if (br == 0)
			return (true);
		if (br > 0)
		{
			if (!(*line))
				continue ;
			if (ft_issetinstr(*line, set))
				continue ;
			else
			{
				printf("Error: Line not valid after map [%s]\n", *line);
				free_null(*line);
				return (false);
			}
		}
	}
}

bool	parse_map(t_vars *vars, int fd, char ***buffer)
{
	char	*line;

	if (!skip_empty_line(&line, fd, CHAR_VALID))
		return (false);
	add_line_tabstr(buffer, line);
	while (gnl(fd, &line) > 0)
	{
		if (!line)
		{
			if (manage_lines_after_map(&line, fd, " "))
				break ;
			else
				return (clean_textures(vars, false, NULL));
		}
		if (!parse_map_line(vars, line) || vars->flag & F_ERROR)
			return (clean_textures(vars, false, NULL));
		add_line_tabstr(buffer, line);
		vars->m.s.h++;
	}
	if (!(vars->flag & F_PLAYER))
	{
		printf("Error: Player not set\n");
		return (clean_textures(vars, false, NULL));
	}
	return (true);
}
