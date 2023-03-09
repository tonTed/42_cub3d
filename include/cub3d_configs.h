/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_configs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:12:22 by tonted            #+#    #+#             */
/*   Updated: 2023/03/09 14:12:26 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_CONFIGS_H
# define CUBE3D_CONFIGS_H

/**
 * @brief General configurations.
 *
 * WIDTH:		width of the window
 * HEIGHT:		height of the window
 * TITLE:		title of the window
 * PIXEL_SIZE:	pixel by map unit
 *
 */
# define WIDTH 1024
# define HEIGHT 688
# define TITLE "cub3d"
# define PIXEL_SIZE 64

/**
 * @brief Player configurations.
 *
 * FOV:		field of view (in radians)
 * 			60° = M_PI / 3
 */
# define FOV M_PI / 3

/**
 * @brief colors
 *
 */
# define ORANGEH 0xFF0080FF
# define REDH 0xFF0000FF

/**
 * @brief Mini map configurations.
 *
 * MM_PIXEL_SIZE:		pixel by minimap unit
 * SHIFT:				separator between units
 * DOT_PLAYER_SIZE:		size of the player dot
 * DOT_PLAYER_COLOR:	color of the player dot
 * RAY_COLOR:			color of the ray
 * RAY_LENGTH:			length of the ray on front of the player
 */
# define MM_PIXEL_SIZE 16
# define SHIFT 1
# define DOT_PLAYER_SIZE 7
# define DOT_PLAYER_COLOR ORANGEH
# define RAY_COLOR REDH
# define RAY_LENGTH 16


#endif