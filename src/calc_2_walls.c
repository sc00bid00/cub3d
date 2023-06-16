/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_2_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:37:05 by kczichow          #+#    #+#             */
/*   Updated: 2023/06/16 13:51:31 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	get_vertical_walls(t_display *display)
{
	if (display->wall->dir == 1)
	{
		if (display->ray->x_off < 0)
		{
			display->wall->texture = display->tex[WE];
			display->wall->offset_x = 1 -((double)((int)(display->ray->y0 * \
				COEFF) % (display->maps->map_s * COEFF)) / \
				((double) display->maps->map_s * COEFF));
		}
		else if (display->ray->x_off > 0)
		{
			display->wall->texture = display->tex[EA];
			display->wall->offset_x = (double)((int)(display->ray->y0 * \
				COEFF) % (display->maps->map_s * COEFF) / \
				((double) display->maps->map_s * COEFF));
		}
	}
}

void	get_horiz_walls(t_display *display)
{
	if (display->wall->dir == 0)
	{
		if (display->ray->y_off < 0)
		{
			display->wall->texture = display->tex[NO];
			display->wall->offset_x = (double)((int)(display->ray->x0 * COEFF) \
				% (display->maps->map_s * COEFF) / \
				((double) display->maps->map_s * COEFF));
		}
		else if (display->ray->y_off > 0)
		{
			display->wall->texture = display->tex[SO];
			display->wall->offset_x = 1 - ((double)((int)(display->ray->x0 * \
				COEFF) % (display->maps->map_s * COEFF)) / \
				((double) display->maps->map_s * COEFF));
		}
	}
}

void	get_wall_dir(t_display *display)
{
	get_vertical_walls(display);
	get_horiz_walls(display);
	reset_offset(display->wall);
}

/* uses pythagoran theorem to return distance from player */
/* must be adjusted to avoid fishbowl effect */
double	dist(t_pos *pos, double bx, double by, double ang)
{
	(void) ang;
	return (sqrt((bx - pos->x) * (bx - pos->x) \
		+ (by - pos->y) * (by - pos->y)));
}
