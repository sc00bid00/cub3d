#include <cub3d.h>

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
        mlx_put_pixel(display->g_img, x_start, y_start, color);

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
