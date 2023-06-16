/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:53:34 by kczichow          #+#    #+#             */
/*   Updated: 2023/06/16 13:44:26 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_minimap(t_display *d)
{
	t_maps	*maps;

	maps = d->maps;
	maps->y = 0;
	maps->y0 = 0;
	while (maps->y0 < d->maps->height_mm && maps->y < maps->max_y)
	{
		maps->x = 0;
		maps->x0 = 0;
		while (maps->x0 < d->maps->width_mm && maps->x < maps->max_x)
		{
			maps->y = (int)(maps->y0 / maps->map_s);
			maps->x = (int)(maps->x0 / maps->map_s);
			if (d->pdata->map[maps->y][maps->x] == '1')
				my_put_pixel_mm(d, maps->x0, maps->y0, get_rgba(0, 0, 100));
			else
				my_put_pixel_mm(d, maps->x0, maps->y0, get_rgba(100, 0, 0));
			maps->x0++;
		}
		maps->y0++;
	}
}

void	draw_rays(t_display *d, t_pos *pos, t_ray *ray)
{
	int	color;

	(void) pos;
	(void) ray;
	color = get_rgba(200, 10, 10);
	d->bresenham->x_start = (int)d->pos->x;
	d->bresenham->y_start = (int)d->pos->y;
	d->bresenham->x_end = (int)d->ray->x0;
	d->bresenham->y_end = (int)d->ray->y0;
	bresenham(d, color);
}
