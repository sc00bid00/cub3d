/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:56:42 by kczichow          #+#    #+#             */
/*   Updated: 2023/05/23 16:57:03 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*	functions implement the DDA - algorithm, that is used to identify */
/*	intersections in grids by simply adding the offsets of x and y until */
/*	a wall is hit */

/* calculate x - offset looking up or down */
void	find_horizontal_intersec(t_display *display, t_pos *pos, t_ray *ray)
{
	if ((ray->a) == 0 || (ray->a == M_PI * 2))
			ray->atan = 1;
	else
		ray->atan = -1 / tan (ray->a);
	ray->dis_h = 100000;
	ray->hx = pos->x;
	ray->hy = pos->y;
	if (ray->a > M_PI && ray->a <= M_PI * 2)
	{
		ray->y0 = ((int)(pos->y / display->maps->map_s)) \
			* display->maps->map_s - 0.001;
		ray->y_off = -display->maps->map_s;
	}
	if (ray->a <= M_PI && ray->a >= 0)
	{
		ray->y0 = ((int)(pos->y / display->maps->map_s)) \
			* display->maps->map_s + display->maps->map_s;
		ray->y_off = display->maps->map_s;
	}
	ray->x0 = pos->x + ((pos->y - ray->y0) * ray->atan);
	ray->x_off = -(ray->y_off) * ray->atan;
}

/*	if ray hits wall, calculate distance, else, add offset and check again */
void	calc_next_h_intersection(t_display *display, t_pos *pos, t_ray *ray)
{
	int	count;

	count = 0;
	while (count < display->maps->max_y)
	{
		ray->y = (int)(ray->y0 / display->maps->map_s);
		ray->x = (int)(ray->x0 / display->maps->map_s);
		if (ray->y >= 0 && ray->x >= 0 && ray->y < display->maps->max_y \
			&& ray->x < display->maps->max_x \
			&& display->pdata->map[ray->y][ray->x] == '1')
		{
			ray->hx = ray->x0;
			ray->hy = ray->y0;
			ray->dis_h = dist(pos, ray->hx, ray->hy, ray->a);
			count = display->maps->max_y;
		}
		else if (ray->y >= 0 && ray->x >= 0 && ray->y < display->maps->max_y
			&& ray->x < display->maps->max_x)
		{
			ray->x0 = ray->x0 + ray->x_off;
			ray->y0 = ray->y0 + ray->y_off;
		}
		count++;
	}
}

/* calculate y offset, looking left or right*/
void	find_vertical_intersec(t_display *display, t_pos *pos, t_ray *ray)
{
	ray->ntan = -tan(ray->a);
	ray->dis_v = 100000;
	ray->vx = pos->x;
	ray->vy = pos->y;
	if (ray->a > M_PI_2 && ray->a <= (3 * M_PI_2))
	{
		ray->x0 = ((int)(pos->x / display->maps->map_s)) \
			* display->maps->map_s - 0.001;
		ray->x_off = -display->maps->map_s;
	}
	if (ray->a <= M_PI_2 || ray->a > (3 * M_PI_2))
	{
		ray->x0 = ((int)(pos->x / display->maps->map_s)) \
			* display->maps->map_s + display->maps->map_s;
		ray->x_off = display->maps->map_s;
	}
	ray->y0 = pos->y + ((pos->x - ray->x0) * ray->ntan);
	ray->y_off = -(ray->x_off) * ray->ntan;
}

/*	if ray hits wall, calculate distance, else, add offset and check again */
void	calc_next_v_intersection(t_display *display, t_pos *pos, t_ray *ray)
{
	int	count;

	count = 0;
	while (count < display->maps->max_y)
	{
		ray->y = (int)(ray->y0 / display->maps->map_s);
		ray->x = (int)(ray->x0 / display->maps->map_s);
		if (ray->y >= 0 && ray->x >= 0 && ray->y < display->maps->max_y \
			&& ray->x < display->maps->max_x \
			&& display->pdata->map[ray->y][ray->x] == '1')
		{
			ray->vx = ray->x0;
			ray->vy = ray->y0;
			ray->dis_v = dist(pos, ray->vx, ray->vy, ray->a);
			count = display->maps->max_y;
		}
		else if (ray->y >= 0 && ray->x >= 0 && ray->y < display->maps->max_y
			&& ray->x < display->maps->max_x)
		{
			ray->x0 = ray->x0 + ray->x_off;
			ray->y0 = ray->y0 + ray->y_off;
		}
		count++;
	}
}

/* check if horizontal or vertical intersection is closer to player and */
/*	set variables for drawing + 3D calculation accordingly*/
void	compare_dist(t_ray *ray, t_wall *wall)
{
	if (ray->dis_h > ray->dis_v)
	{
		ray->x0 = ray->vx;
		ray->y0 = ray->vy;
		ray->dis_t = ray->dis_v;
		wall->dir = 1;
	}
	else if (ray->dis_h <= ray->dis_v)
	{
		ray->x0 = ray->hx;
		ray->y0 = ray->hy;
		ray->dis_t = ray->dis_h;
		wall->dir = 0;
	}
}
