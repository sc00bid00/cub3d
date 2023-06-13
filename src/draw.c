/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:26:19 by kczichow          #+#    #+#             */
/*   Updated: 2023/06/13 15:00:01 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cub3d.h>

void	draw_line(t_display *d, int *dist, int *s, int err, int e2)
{
	(void)d;
	(void)dist;
	(void)s;
	(void)err;
	(void)e2;

	int color = get_rgba(200, 10, 10);
	 while (1 && d->pos->x < WIDTH && d->pos->y < HEIGHT && d->pos->x > 0 && d->pos->y > 0)
    {
        mlx_put_pixel(d->mm_img, d->pos->x, d->pos->y, color);

        if (d->pos->x == d->ray->x0 && d->pos->y == d->ray->y0)
        {
            break;
        }
		e2 = 2 * err;
        if (e2 > -dist[1])
        {
            err -= dist[1];
            d->pos->x += s[0];
        }

        if (e2 < dist[0])
        {
            err += dist[0];
            d->pos->y += s[1];
        }
    }
}

/*	bresenham line draw function */
/*	calculates differences between start and end points	*/
/*	determines direction of line in x and y directions */
void bresenham(t_display *d, int x_start, int y_start, int x_end, int y_end)
{
	int dist[2];
	int s[2];
	int err;
	int e2 = 0;
	int color = get_rgba(200, 10, 10);
	// if (color == 270)
    //     color = get_rgba(200, 200, 30);
    // Calculate the differences between the start and end points
    // int dx = abs(x_end - x_start);
	dist[0] = abs((int)d->ray->x0 - (int)d->pos->x);
    // int dy = abs(y_end - y_start);
	dist[1] = abs((int)d->ray->y0 - (int)d->pos->y);
	if (d->pos->x < d->ray->x0)
		s[0] = 1;
	else
		s[0] = -1;
	if (d->pos->y < d->ray->y0)
		s[1] = 1;
	else
		s[1] = -1;
    // Initialize the error term and the step values
    err = dist[0] - dist[1];
    // int e2;
	// draw_line(d, dist, s, err, e2);
    // Loop through each point along the line and plot the pixels
    while (1 && x_start < WIDTH && y_start < HEIGHT && x_start > 0 && y_start > 0)
    {
        // mlx_put_pixel(d->mm_img, x_start, y_start, color);
		my_put_pixel_mm(d, x_start, y_start, color);

        if (x_start == x_end && y_start == y_end)
        {
            break;
        }
		e2 = 2 * err;
        if (e2 > -dist[1])
        {
            err -= dist[1];
            x_start += s[0];
        }

        if (e2 < dist[0])
        {
            err += dist[0];
            y_start += s[1];
        }
    }
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
			if ( y0 > HEIGHT / 2)
				my_put_pixel(d->f_c_img, x0, y0, d->pdata->colors_fc[F]);
			else
				my_put_pixel(d->f_c_img, x0, y0, d->pdata->colors_fc[C]);
			y0++;
		}
		x0++;
	}
}
