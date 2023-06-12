/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 09:49:54 by kczichow          #+#    #+#             */
/*   Updated: 2023/06/12 11:12:47 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	reset_angles(t_display *display)
{
	if (display->ray->a <= 0)
		display->ray->a += 2 * M_PI;
	if (display->ray->a >= 2 * M_PI)
		display->ray->a -= 2 * M_PI;
}

/*	set viewer angle to 60 degrees; calculate both horizontal and vertical	*/
/*	intersections with grid. Find closest vertical and horizontal wall. */
/*	compare distances and select closer distance to determine ray length. */
void	render(t_display *display, t_pos *pos, t_ray *ray, t_wall *wall)
{
	ray->a = pos->a - (DR * 30);
	reset_angles(display);
	ray->r = 0;
	wall->x0 = 0;
	while (ray->r < ray->ray_max)
	{
		find_horizontal_intersec(display, pos, ray);
		calc_next_h_intersection(display, pos, ray);
		find_vertical_intersec(display, pos, ray);
		calc_next_v_intersection(display, pos, ray);
		compare_dist(ray, wall);
		get_wall_dir(display);
		draw_rays_2D(display, pos, ray);
		calculate_3D_param(display, wall, pos, ray);
		draw_column(display, ray, wall, display->maps);
		ray->a += DR * 60/ray->ray_max;
		reset_angles(display);
		ray->r++;
	}
}

