/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 13:09:41 by tonted            #+#    #+#             */
/*   Updated: 2023/01/14 13:13:13 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/libft/include/libft.h"
#include "../libraries/MLX42/include/MLX42/MLX42.h"

#include <stdio.h>

typedef struct s_vars {
	mlx_t	*mlx;
}	t_vars;

/* hooks */
void    hook_keyboard(mlx_t *mlx);

/* parsing */
int32_t parse_file_map(char *file, t_vars *vars);

/* initialization */
int32_t	init_assets(t_vars *vars);

/* development */
# define WHOAMI printf(GRN"Function "BMAG"%s"GRN" ran "BGRN"SUCCESSFULLY\n"RESET, __func__);