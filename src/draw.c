/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:26:19 by kczichow          #+#    #+#             */
/*   Updated: 2023/05/23 17:00:26 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cub3d.h>

/* specify line details */
void	draw_line(t_display *display, double posx, double posy)
{
	double	x_end;
	double	y_end;
	int		length;

	length = 20;
	x_end = posx + length * cos(display->pos->a);
	y_end = posy + length * sin(display->pos->a);
	draw_line_bresenham(display, posx, posy, x_end, y_end, 270);
}

/* to be updated with Luca's Bresenham function */
void draw_line_bresenham(t_display *display, int x_start, int y_start, int x_end, int y_end, int color)
{
	if (color == 270)
        color = get_rgba(200, 200, 30);
    // Calculate the differences between the start and end points
    int dx = abs(x_end - x_start);
    int dy = abs(y_end - y_start);

    // Determine the direction of the line in both the x and y directions
    int sx = x_start < x_end ? 1 : -1;
    int sy = y_start < y_end ? 1 : -1;

    // Initialize the error term and the step values
    int err = dx - dy;
    int e2;

    // Loop through each point along the line and plot the pixels
    while (1 && x_start < WIDTH && y_start < HEIGHT && x_start > 0 && y_start > 0)
    {
        mlx_put_pixel(display->mm_img, x_start, y_start, color);

        if (x_start == x_end && y_start == y_end)
        {
            break;
        }
		e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x_start += sx;
        }

        if (e2 < dx)
        {
            err += dx;
            y_start += sy;
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
	if (x < 0)
		x = 0;
	mlx_put_pixel(display->mm_img, x, y, color);
}

/* function protects regular map */
void	my_put_pixel(mlx_image_t *img, double x, double y, int color)
{
	if (y > HEIGHT)
		y = HEIGHT;
	if (y < 0)
		y = 0;
	if (x > WIDTH)
		x = WIDTH;
	if (x < 0)
		x = 0;
	mlx_put_pixel(img, x, y, color);
}

/* floor and ceiling have their own image layer*/
void	draw_floor_ceiling(t_display *display)
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
				// my_put_pixel(display->f_c_img, x0, y0, display->pdata->colors_fc[0]);
				my_put_pixel(display->f_c_img, x0, y0, get_rgba(190, 123, 67));
			else
				my_put_pixel(display->f_c_img, x0, y0, get_rgba(0, 30, 220));
				// my_put_pixel(display->f_c_img, x0, y0, display->pdata->colors_fc[1]);
			y0++;
		}
		x0++;
	}
}
