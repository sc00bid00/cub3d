/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:43:29 by kczichow          #+#    #+#             */
/*   Updated: 2023/06/13 14:46:46 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/* uses pythagoran theorem to return distance from player */
/* must be adjusted to avoid fishbowl effect */
double	dist(t_pos *pos, double bx, double by, double ang)
{
	(void) ang;
	return (sqrt((bx - pos->x) * (bx - pos->x) \
		+ (by - pos->y) * (by - pos->y)));
}

/*	GET_RGBA
*	----------
*	Function combines four individual channel bytes into a single integer using
*	bit-shifting. The last byte is for transparency and always set to 255.
*/
uint32_t	get_rgba(uint8_t red, uint8_t green, uint8_t blue)
{
	return ((uint32_t)(red << 24 | green << 16 | blue << 8 | 255));
}
