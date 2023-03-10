/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:07:15 by tonted            #+#    #+#             */
/*   Updated: 2023/03/08 10:07:17 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	gnl_joint(char **line, char *buffer)
{
	char	*tmp;

	if (*line == NULL)
		*line = ft_strdup(buffer);
	else
	{
		tmp = *line;
		*line = ft_strjoin(*line, buffer);
		free_null(tmp);
	}
}

int	gnl(int fd, char **line)
{
	int		br;
	char	buffer[2];

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
		gnl_joint(line, buffer);
	}
}
