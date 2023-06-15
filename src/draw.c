/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:26:19 by kczichow          #+#    #+#             */
/*   Updated: 2023/06/15 16:55:11 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_line(t_display *d, int color)
{
	while (1 && d->bresenham->x_start < WIDTH && \
		d->bresenham->y_start < HEIGHT && d->bresenham->x_start > 0 && \
		d->bresenham->y_start > 0)
	{
		my_put_pixel_mm(d, d->bresenham->x_start, d->bresenham->y_start, color);
		if (d->bresenham->x_start == d->bresenham->x_end && \
			d->bresenham->y_start == d->bresenham->y_end)
		{
			break ;
		}
		d->bresenham->e2 = 2 * d->bresenham->err;
		if (d->bresenham->e2 > -d->bresenham->dist[1])
		{
			d->bresenham->err -= d->bresenham->dist[1];
			d->bresenham->x_start += d->bresenham->s[0];
		}
		if (d->bresenham->e2 < d->bresenham->dist[0])
		{
			d->bresenham->err += d->bresenham->dist[0];
			d->bresenham->y_start += d->bresenham->s[1];
		}
	}
}

/*	bresenham line draw function */
/*	calculates differences between start and end points	*/
/*	determines direction of line in x and y directions */
// void bresenham(t_display *d, int x_start, int y_start, int x_end, int y_end)
void	bresenham(t_display *d, int color)
{
	d->bresenham->dist[0] = abs(d->bresenham->x_end - d->bresenham->x_start);
	d->bresenham->dist[1] = abs(d->bresenham->y_end - d->bresenham->y_start);
	if (d->bresenham->x_start < d->bresenham->x_end)
		d->bresenham->s[0] = 1;
	else
		d->bresenham->s[0] = -1;
	if (d->pos->y < d->ray->y0)
		d->bresenham->s[1] = 1;
	else
		d->bresenham->s[1] = -1;
	d->bresenham->err = d->bresenham->dist[0] - d->bresenham->dist[1];
	draw_line(d, color);
}

/* function protects minimap */
void	my_put_pixel_mm(t_display *display, double x, double y, int color)
{
	if (y > display->maps->height_mm)
		y = display->maps->height_mm - 1;
	if (y < 0)
		y = 0;
	if (x > display->maps->width_mm)
		x = display->maps->width_mm - 1;
	if (x <= 0)
		x = 0;
	mlx_put_pixel(display->mm_img, x, y, color);
}

/* function protects regular map */
void	my_put_pixel(mlx_image_t *img, double x, double y, int color)
{
	if (y >= HEIGHT - 1)
		y = HEIGHT - 1;
	if (y <= 0)
		y = 0;
	if (x >= WIDTH - 1)
		x = WIDTH -1 ;
	if (x <= 0)
		x = 0;
	mlx_put_pixel(img, x, y, color);
}

/* floor and ceiling have their own image layer*/
void	draw_floor_ceiling(t_display *d)
{
	int	x0;
	int	y0;

	x0 = 0;
	while (x0 < WIDTH && x0 >= 0)
	{
		y0 = 0;
		while (y0 < HEIGHT && y0 >= 0)
		{
			if (y0 > HEIGHT / 2)
				my_put_pixel(d->f_c_img, x0, y0, d->pdata->colors_fc[F]);
			else
				my_put_pixel(d->f_c_img, x0, y0, d->pdata->colors_fc[C]);
			y0++;
		}
		x0++;
	}
}
