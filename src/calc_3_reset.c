/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:12:43 by kczichow          #+#    #+#             */
/*   Updated: 2023/06/15 14:23:24 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	reset_offset(t_wall *wall)
{
	while (wall->offset_x < 0)
		wall->offset_x += 1;
	while (wall->offset_x > 1)
		wall->offset_x -= 1;
}

void	reset_player_angle(t_pos *pos)
{
	if (pos->a <= 0)
		pos->a += 2 * M_PI;
	if (pos->a >= 2 * M_PI)
		pos->a -= 2 * M_PI;
}

void	reset_ray_angle(t_display *display)
{
	if (display->ray->a <= 0)
		display->ray->a += 2 * M_PI;
	if (display->ray->a >= 2 * M_PI)
		display->ray->a -= 2 * M_PI;
}
