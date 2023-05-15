/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays2d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 09:49:54 by kczichow          #+#    #+#             */
/*   Updated: 2023/05/15 10:57:36 by kczichow         ###   ########.fr       */
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
    "10111101",
    "11111111"
};

void	reset_angles(t_display *display)
{
	if (display->ray->a < 0)
		display->ray->a += 2 * M_PI;
	if (display->ray->a > 2 * M_PI)
		display->ray->a -= 2 * M_PI;
}

/*	if ray hits wall, calculate distance, else, add offset and check again */
void	calc_next_h_intersection(t_display *display, t_pos *pos, t_ray *ray)
{
	int count;

	count = 0;
	while (count < display->maps->max_y)
	{
		ray->y = (int) (ray->y0 / mapS);
		ray->x = (int) (ray->x0 / mapS);
		if (ray->y >= 0 && ray->x >= 0 && ray->y < display->maps->max_y 
			&& ray->x < display->maps->max_x && map[ray->y][ray->x] == '1')
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
		ray->y0 = ((int)(pos->y/mapS)) * mapS - 1;
		ray->y_off = -mapS;
	}
	if (ray->a <= M_PI && ray->a >= 0)
	{
		ray->y0 = ((int)(pos->y/mapS)) * mapS + mapS;
		ray->y_off = mapS;
	}
	ray->x0 = pos->x + ((pos->y - ray->y0) * ray->atan);
	ray->x_off = -(ray->y_off) * ray->atan;
	calc_next_h_intersection(display, pos, ray);
}

/*	if ray hits wall, calculate distance, else, add offset and check again */
void	calc_next_v_intersection(t_display *display, t_pos *pos, t_ray *ray)
{
	int count;

	count = 0;
	while (count < display->maps->max_y)
	{
		ray->y = (int) (ray->y0 / mapS);
		ray->x = (int) (ray->x0 / mapS);
		if (ray->y >= 0 && ray->x >= 0 && ray->y < display->maps->max_y
			&& ray->x < display->maps->max_x && map[ray->y][ray->x] == '1')
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

/* calculate y offset, looking left or right*/
void	find_vertical_intersec(t_display *display, t_pos *pos, t_ray *ray)
{
	int count;
	
	count = 0;
		ray->ntan = -tan(ray->a);
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
		ray->y0 = pos->y + ((pos->x - ray->x0) * ray->ntan);
		ray->y_off = -(ray->x_off) * ray->ntan;
		calc_next_v_intersection(display, pos, ray);
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
		wall->shading = get_rgba(0,133,120);
	}
	else if (ray->dis_h < ray->dis_v)
	{
		ray->x0 = ray->hx;
		ray->y0 = ray->hy;
		ray->dis_t = ray->dis_h;
		wall->shading = get_rgba(0,89,79);
	}
}

void	draw_rays(t_display *display, t_pos *pos, t_ray *ray)
{
	if (pos->x > 0 && pos->x < WIDTH_MM && ray->x0 > 0 && ray->x0 < WIDTH_MM - 1
		&& pos->y > 0 && pos->y < HEIGHT_MM && ray->y0 > 0 && ray->y0 < HEIGHT_MM)
		{
			draw_line_bresenham(display, pos->x, pos->y, ray->x0, ray->y0, get_rgba(200, 10, 10)); // red
		}		
}


/*	set viewer angle to 60 degrees; calculate both horizontal and vertical	*/
/*	intersections with grid. Find closest vertical and horizontal wall. */
/*	compare distances and select closer distance to determine ray length. */
void	calc_rays(t_display *display, t_pos *pos, t_ray *ray, t_wall *wall)
{
	ray->a = pos->a - (DR * 30);
	reset_angles(display);
	ray->r = 0;
	wall->x0 = 0;
	while (ray->r < ray->ray_max)
	{
		find_horizontal_intersec(display, pos, ray);
		find_vertical_intersec(display, pos, ray);
		compare_dist(ray, wall);
		draw_rays(display, pos, ray);
		calculate_3D_param(wall, pos, ray);
		draw_column(display, ray, wall, display->maps);
		ray->a += DR * 60/ray->ray_max;
		reset_angles(display);
		ray->r++;
	}
}

void	draw_minimap(t_display *display)
{
	drawMap2D(display);
	draw_player_mm(display);
}


/*	function is called for each map coordinate and draws pixel in corresponding
	cube */

void	draw_cube(t_display *display, bool wall)
{
	int i;
	int j;
	t_maps	*maps;

	i = 0;
	j = 0;
	maps = display->maps;
    while (i < mapS - 1 && maps->x0 < WIDTH_MM && maps->y0 < HEIGHT_MM)
    {
    	if (wall)
			mlx_put_pixel(display->mm_img, maps->x0, maps->y0, get_rgba(0,80,100));
		else
			mlx_put_pixel(display->mm_img, maps->x0, maps->y0, get_rgba(100,100,100));
        j = 1;
		maps->y0 = (maps->y * mapS);
		while(j < mapS - 1 && maps->x0 < WIDTH_MM && maps->y0 < HEIGHT_MM)
		{
			if (wall)
				mlx_put_pixel(display->mm_img, maps->x0, maps->y0, get_rgba(0,80,100));
			else
				mlx_put_pixel(display->mm_img, maps->x0, maps->y0, get_rgba(100,100,100));
			maps->y0++;
			j++;
		}
		maps->x0++;
		i++;
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
			maps->y0 = (maps->y * mapS);
			maps->x0 = (maps->x * mapS);
			if (map[maps->y][maps->x] == '1')
				draw_cube(display, true);
			else
				draw_cube(display, false);
			maps->x++;
		}
		maps->y++;
	}
}