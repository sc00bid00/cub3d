/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:28:32 by kczichow          #+#    #+#             */
/*   Updated: 2023/05/23 16:49:10 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*	remove fisheye effet with cosinus, calculate line height using distance, */
/*	calculate offset from middle horizontal line */
void	calculate_3D_param(t_display *d, t_wall *wall, t_pos *pos, t_ray *ray)
{
	float	angle_dist;
	
	wall->dis_t = ray->dis_t * HEIGHT/d->maps->height_mm;
	angle_dist = pos->a - ray->a;
	if (angle_dist < 0)
		angle_dist += 2 * M_PI;
	if (angle_dist > 2 * M_PI)
		angle_dist -= 2 * M_PI;
	wall->dis_t = wall->dis_t * cos(angle_dist);
	wall->line_h = (HEIGHT * mapS) / (wall->dis_t);
	if (wall->line_h > HEIGHT)
		wall->line_h = HEIGHT - 1;
	wall->line_w = WIDTH / pos->fov;
	wall->line_off = (HEIGHT - wall->line_h) / 2;
}
// double	norm_x(t_wall *wall)
// {
// 	if (wall->x0 > 64)
// 	{

// 	}
// }

void	draw_column(t_display *display, t_ray *ray, t_wall *wall, t_maps *maps)
{
	double start;
	double end;
	double j;
	double x;
	if (wall->x0 > 64)
		x = (int)wall->x0 % 64;
	else
		x = wall->x0;
	int i;
	(void) maps;
	i = 0;
	while (i <= WIDTH / ray->ray_max)
	{
		start = HEIGHT / 2 - wall->line_h / 2;
		end = HEIGHT / 2 + wall->line_h / 2;
		j = start;
		while (j < end)
		{
			int texel = 0;
			double offset = (j - start) / (end - start);
			double offset_x = x / 64;
			// if (offset_x > 1)
			// 	offset_x = 1;	
			// offset_x = offset_x * cos(display->pos->a - ray->a);
			// printf(" offset x is %f\n", offset_x);
			// texel = texel * offset;
			if (ray->hx - (int) ray->hx == 0) {
				// texel = img_pixel(ray->hy - (int) ray->hy, offset, display->wall->texture);
				texel = img_pixel(offset_x, offset, display->wall->texture);
			} else {
				texel = img_pixel(offset_x, offset, display->wall->texture);
				// texel = img_pixel(ray->hx - (int) ray->hx, offset, display->wall->texture);
			}
			// printf("%x\n", texel);
			my_put_pixel(display->s_img, wall->x0, j, texel);
			j++;
		}
		wall->x0++;
		i++;
	}
}
