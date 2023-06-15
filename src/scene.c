/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:28:32 by kczichow          #+#    #+#             */
/*   Updated: 2023/06/15 14:48:02 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*	remove fisheye effet with cosinus, calculate line height using distance, */
/*	calculate offset from middle horizontal line */
/*	wall->line_w equals distance from projection plane */
void	calc_3d_param(t_display *d, t_wall *wall, t_pos *pos, t_ray *ray)
{
	float	angle_dist;

	wall->dis_t = ray->dis_t * HEIGHT / d->maps->height_mm;
	angle_dist = pos->a - ray->a;
	if (angle_dist < 0)
		angle_dist += 2 * M_PI;
	if (angle_dist > 2 * M_PI)
		angle_dist -= 2 * M_PI;
	wall->dis_t = wall->dis_t * cos(angle_dist);
	wall->line_w = (WIDTH / 2) / tan(pos->fov / 2);
	if (wall->dis_t <= d->maps->map_s)
		wall->line_h = HEIGHT;
	else
		wall->line_h = MAPS * wall->line_w / wall->dis_t;
	wall->line_off = (HEIGHT - wall->line_h) / 2;
}

void	draw_column(t_display *display, t_ray *ray, t_wall *wall)
{
	double	start;
	double	end;
	double	offset;
	double	j;
	int		i;

	start = HEIGHT / 2 - wall->line_h / 2;
	end = HEIGHT / 2 + wall->line_h / 2;
	i = 0;
	while (i < WIDTH / ray->ray_max)
	{
		j = start;
		while (j < end)
		{
			offset = (j - start) / (end - start);
			my_put_pixel(display->s_img, wall->x0, j, \
				img_pixel(wall->offset_x, offset, display->wall->texture));
			j++;
		}
		wall->x0++;
		i++;
	}
}
