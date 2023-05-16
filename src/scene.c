/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:28:32 by kczichow          #+#    #+#             */
/*   Updated: 2023/05/16 14:58:04 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*	remove fisheye effet with cosinus, calculate line height using distance, */
/*	calculate offset from middle horizontal line */
void	calculate_3D_param(t_display *display, t_wall *wall, t_pos *pos, t_ray *ray)
{
	wall->dis_t = ray->dis_t * HEIGHT/display->maps->height_mm;
	wall->ca = pos->a - ray->a;
	if (wall->ca < 0)
		wall->ca += 2 * M_PI;
	if (wall->ca > 2 * M_PI)
		wall->ca -= 2 * M_PI;
	wall->dis_t = wall->dis_t * cos(wall->ca);
	wall->line_h = (HEIGHT * display->maps->map_s * 4) / (wall->dis_t);
	if (wall->line_h > HEIGHT)
		wall->line_h = HEIGHT;
	wall->line_off = (HEIGHT - wall->line_h) / 2;
}

void	draw_column(t_display *display, t_ray *ray, t_wall *wall, t_maps *maps)
{
	int i;
	int j;
	(void) maps;
	i = 0;
	j = 0;
	while (i <= WIDTH / ray->ray_max)
	{
		j = 0;
		wall->y0 = 0;
		while (j < HEIGHT-1 && wall->x0 >=0 && wall->x0 <= WIDTH)
		{
			if (wall->y0 >= wall->line_off && wall->y0 <= (HEIGHT - wall->line_off))
				my_put_pixel(display->s_img, wall->x0, wall->y0, wall->shading );
			// my_put_pixel(display->s_img, wall->x0, wall->y0, get_rgba(134, 200, 188));
			wall->y0++;
			j++;
		}
		wall->x0++;
		i++;
	}
}
