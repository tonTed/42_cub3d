/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parse.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:12:30 by tonted            #+#    #+#             */
/*   Updated: 2023/03/09 14:12:32 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_PARSE_H
# define CUB3D_PARSE_H

/**
 * @brief Flags for the map parsing.
 *
 * F_NORTH:		00000001
 * F_SOUTH:		00000010
 * F_WEST:		00000100
 * F_EAST:		00001000
 * F_FLOOR:		00010000
 * F_CEILING:	00100000
 * TOTAL:		00111111
 * F_PLAYER:	01000000
 * F_ERROR:		10000000
 */
# define F_NORTH 0x1
# define F_SOUTH 0x2
# define F_WEST 0x4
# define F_EAST 0x8
# define F_FLOOR 0x10
# define F_CEILING 0x20
# define TOTAL 0x3F
# define F_PLAYER 0x40
# define F_ERROR 0x80



#endif
