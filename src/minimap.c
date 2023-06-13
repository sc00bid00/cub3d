/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:53:34 by kczichow          #+#    #+#             */
/*   Updated: 2023/06/13 13:02:31 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void	draw_minimap(t_display *display)
{
	drawMap2D(display);
	// exit (0);
	draw_player_mm(display);
}

void drawMap2D(t_display *display)
{
	t_maps	*maps;

	maps = display->maps;
	maps->y = 0;
	maps->y0 = 0;
	while (maps->y0 < display->maps->height_mm && maps->y < maps->max_y)
	{
		maps->x = 0;
		maps->x0 = 0;
		while (maps->x0 < display->maps->width_mm && maps->x < maps->max_x)
		{
			maps->y = (int)(maps->y0 / maps->map_s);
			maps->x = (int)(maps->x0 / maps->map_s);
			if (display->pdata->map[maps->y][maps->x] == '1')
				my_put_pixel_mm(display, maps->x0, maps->y0, get_rgba(0,0,100));
			else
				my_put_pixel_mm(display, maps->x0, maps->y0, get_rgba(100,0,0));
			maps->x0++;
		}
		maps->y0++;
	}
}

void	draw_rays_2D(t_display *display, t_pos *pos, t_ray *ray)
{
	if (pos->x > 0 && pos->x < display->maps->width_mm && ray->x0 > 0 && ray->x0 < display->maps->width_mm - 1
		&& pos->y > 0 && pos->y < display->maps->height_mm && ray->y0 > 0 && ray->y0 < display->maps->height_mm)
		{
			draw_line_bresenham(display, pos->x, pos->y, ray->x0, ray->y0, get_rgba(200, 10, 10)); // red
		}
}

void	draw_player_mm(t_display *display)
{
	my_put_pixel_mm(display, display->pos->x, display->pos->y, get_rgba(255,255,255));
}
