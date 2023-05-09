/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays2d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 09:49:54 by kczichow          #+#    #+#             */
/*   Updated: 2023/05/09 16:13:46 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cub3d.h>

char *map[] = {
    "11111111",
    "10000001",
    "10111101",
    "10000001",
    "10000001",
    "10000001",
    "10000001",
    "11111111"
};

void	draw_rays(t_display *display, t_pos *pos, t_ray *ray)
{
	int	count;
	float atan;
	float ntan;
	int r;

	// ray->a = pos->a;
	ray->a = pos->a - DR * 30;
	if (ray->a < 0)
		ray->a += 2 * M_PI;
	if (ray->a > 2 * M_PI)
		ray->a -= 2 * M_PI;

	for (r = 0; r < 60; r++)
	{
		count = 0;
		//find horizontal intersections
		if ((ray->a) == 0 || (ray->a == M_PI * 2))
			atan = 1;
		else
			atan = -1 / tan (ray->a);
		ntan = -tan(ray->a);
		ray->dis_h = 100000;
		ray->hx = pos->x;
		ray->vx = pos->y; 
		if (ray->a > M_PI && ray->a <= M_PI * 2)
		{
			ray->y0 = ((int)(pos->y/mapS)) * mapS - 1;
			ray->y_off = -mapS;
		}
		if (ray->a <= M_PI && ray->a >= 0)
		{
			ray->y0 = ((int)(pos->y/mapS)) * mapS + mapS;
			ray->y_off = mapS;
		}
		ray->x0 = pos->x + ((pos->y - ray->y0) * atan);
		ray->x_off = -(ray->y_off) * atan;
		while (count < display->maps->max_y)
		{
			ray->y = (int) (ray->y0 / mapS);
			ray->x = (int) (ray->x0 / mapS);
			if (ray->y >= 0 && ray->x >= 0 && ray->y < display->maps->max_y && ray->x < display->maps->max_x && map[ray->y][ray->x] == '1')
			{
				ray->hx = ray->x0;
				ray->hy = ray->y0;
				ray->dis_h = dist(pos, ray->hx, ray->hy, ray->a);
				count = display->maps->max_y;
			}
			else if (ray->y >= 0 && ray->x >= 0 && ray->y < display->maps->max_y && ray->x < display->maps->max_x)
			{
				ray->x0 = ray->x0 + ray->x_off;
				ray->y0 = ray->y0 + ray->y_off;
			}
			count++;
		}

		//find vertical intersections
		count = 0;
		ray->dis_v = 100000;
		ray->vx = pos->x;
		ray->vy = pos->y;
		if (ray->a > M_PI_2 && ray->a <= (3 * M_PI_2))
		{
			ray->x0 = ((int)(pos->x/mapS)) * mapS - 1;
			ray->x_off = -mapS;
		}
		if (ray->a <= M_PI_2 || ray->a >= (3 * M_PI_2))
		{
			ray->x0 = ((int)(pos->x/mapS)) * mapS + mapS;
			ray->x_off = mapS;
		}
		ray->y0 = pos->y + ((pos->x - ray->x0) * ntan);
		ray->y_off = -(ray->x_off) * ntan;
		while (count < display->maps->max_y)
		{
			ray->y = (int) (ray->y0 / mapS);
			ray->x = (int) (ray->x0 / mapS);
			if (ray->y >= 0 && ray->x >= 0 && ray->y < display->maps->max_y && ray->x < display->maps->max_x && map[ray->y][ray->x] == '1')
			{
				ray->vx = ray->x0;
				ray->vy = ray->y0;
				ray->dis_v = dist(pos, ray->vx, ray->vy, ray->a);
				count = display->maps->max_y;
			}
			else if (ray->y >= 0 && ray->x >= 0 && ray->y < display->maps->max_y && ray->x < display->maps->max_x)
			{
				ray->x0 = ray->x0 + ray->x_off;
				ray->y0 = ray->y0 + ray->y_off;
			}
			count++;
		}
		if (ray->dis_h > ray->dis_v)
		{
			ray->x0 = ray->vx;
			ray->y0 = ray->vy;
		}
		else if (ray->dis_h < ray->dis_v)
		{
			ray->x0 = ray->hx;
			ray->y0 = ray->hy;
		}
		if (pos->x > 0 && pos->x < WIDTH && ray->x0 > 0 && ray->x0 < WIDTH - 1 && pos->y > 0 && pos->y < HEIGHT && ray->y0 > 0 && ray->y0 < HEIGHT)		
				draw_line_bresenham(display, pos->x, pos->y, ray->x0, ray->y0, get_rgba(200, 10, 10)); // red
		
		ray->a += DR;
		if (ray->a < 0)
			ray->a += 2 * M_PI;
		if (ray->a > 2 * M_PI)
			ray->a -= 2 * M_PI;
	}
}

/*	iterates through coordinate system */
void drawMap2D(t_display *display)
{
	t_maps	*maps;

	maps = display->maps;
	maps->x = 0;
	maps->y = 0;
	maps->x0 = 0;
	maps->y0 = 0;
	while (maps->y < maps->max_y)
	{
		maps->x = 0;
		maps->x0 = 0;
		while (maps->x < maps->max_x)
		{
			maps->y0 = (maps->y * display->maps->y_coeff);
			maps->x0 = (maps->x * display->maps->x_coeff);
			if (map[maps->y][maps->x] == '1')
				draw_cube(display, true);
			else
				draw_cube(display, false);
			maps->x++;
		}
		maps->y++;
	}
}