/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:59:25 by lsordo            #+#    #+#             */
/*   Updated: 2023/05/05 11:03:55 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*	CUB3D
*	--------
*	create image, link hooks and place the image within the window.
*	It calls the drawing function.
*/

void	cub3d(char **argv, t_display *display)
{
	(void)	argv;

	display->g_img = mlx_new_image(display->mlx, WIDTH, HEIGHT);
	ft_memset(display->g_img->pixels, COLOR, display->g_img->width \
			* display->g_img->height * sizeof(int32_t));
	mlx_key_hook(display->mlx, &my_keyhook, display);
	// mlx_scroll_hook(display->mlx, &my_scrollhook, display);
	mlx_loop_hook(display->mlx, &my_hook, display);
	// draw_fractal(display);
	drawMap2D(display);
	draw_player(display);
	draw_line(display);
	mlx_image_to_window(display->mlx, display->g_img, 0, 0);
	mlx_loop(display->mlx);
	return ;
}
/*	MY_KEYHOOK
*	------------
*	function is called by MLX lib function and specifies the actions to be
*	executed, if a particular key is being pressed. Void parameter has to be
*	assigned.
*	Press esc: clean up function is called: window closes + pointers freed.
*	Press m: switch to mandelbrot
*	Press j: switch to julia
*	Press c: change color
*/

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	mlx_t		*mlx;
	t_display	*display;
	(void) keydata;

	display = param;
	mlx = display->mlx;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);

	// if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
	// {
	// 	change_color(image);
	// 	draw_fractal(image);
	// }
	// if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
	// {
	// 	image->set->settype = 1;
	// 	draw_fractal(image);
	// }
	// if (keydata.key == MLX_KEY_J && keydata.action == MLX_PRESS)
	// {
	// 	image->set->settype = 2;
	// 	draw_fractal(image);
	// }
}

void	my_hook(void *param)
{
	t_display	*display;

	display = param;
	if (mlx_is_key_down(display->mlx, MLX_KEY_W))
	{
		ft_memset(display->g_img->pixels, COLOR, display->g_img->width \
			* display->g_img->height * sizeof(int32_t));
		display->pos->x += display->pos->dx;
		display->pos->y += display->pos->dy;
	}
	if (mlx_is_key_down(display->mlx, MLX_KEY_S))
	{
		ft_memset(display->g_img->pixels, COLOR, display->g_img->width \
			* display->g_img->height * sizeof(int32_t));
		display->pos->x -= display->pos->dx;
		display->pos->y -= display->pos->dy;
	}
	if (mlx_is_key_down(display->mlx, MLX_KEY_A))
	{
		ft_memset(display->g_img->pixels, COLOR, display->g_img->width \
			* display->g_img->height * sizeof(int32_t));
		display->pos->a -=0.1;
		if(display->pos->a < 0)
			display->pos->a += 2 * M_PI;
		display->pos->dx = cos(display->pos->a) * 5;
		display->pos->dy = sin(display->pos->a) * 5;
		// display->pos->x -= display->pos->dx;
		// display->pos->x -= 5.0;
	}
	if (mlx_is_key_down(display->mlx, MLX_KEY_D))
	{
		ft_memset(display->g_img->pixels, COLOR, display->g_img->width \
			* display->g_img->height * sizeof(int32_t));
		display->pos->a +=0.1;
		if(display->pos->a > 2 * M_PI)
			display->pos->a -= 2 * M_PI;
		display->pos->dx = cos(display->pos->a) * 5;
		display->pos->dy = sin(display->pos->a) * 5;
		// display->pos->x += display->pos->dx;
		// display->pos->x += 5.0;
	}
	drawMap2D(display);
	draw_line(display);
	draw_player(display);
}

/* specify line details */

void	draw_line(t_display *display)
{
	float	x_end;
	float	y_end;
	int		length;

	length = 20;
	x_end = display->pos->x + length * cos(display->pos->a);
	y_end = display->pos->y + length * sin(display->pos->a);
	draw_line_bresenham(display, display->pos->x, display->pos->y, x_end, y_end);
}


/* to be updated with Luca's Bresenham function */
void draw_line_bresenham(t_display *display, int x_start, int y_start, int x_end, int y_end)
{
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
        mlx_put_pixel(display->g_img, x_start, y_start, get_rgba(200, 200, 30));

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

void	draw_player(t_display *display)
{
	my_put_pixel(display);
}

void	my_put_pixel(t_display *display)
{
	if (display->pos->y > HEIGHT)
		display->pos->y = HEIGHT-1;
	if (display->pos->y < 0)
		display->pos->y = 0;
	if (display->pos->x > WIDTH)
		display->pos->x = WIDTH-1;
	if (display->pos->x < 0)
		display->pos->x = 0;
	mlx_put_pixel(display->g_img, display->pos->x, display->pos->y, get_rgba(255,255,255));
}


/*	GET_RGBA
*	----------
*	Function combines four individual channel bytes into a single integer using
*	bit-shifting. The last byte is for transparency and always set to 255.
*/
uint32_t	get_rgba(uint8_t red, uint8_t green, uint8_t blue)
{
	return ((uint32_t)(red << 24 | green << 16 | blue << 8 | 255));
}

char *map[] = {
    "11111111",
    "10100001",
    "10111101",
    "10100101",
    "10100101",
    "10111101",
    "10000001",
    "11111111"
};

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
    while (i < display->maps->x_coeff - 1 && maps->xo < WIDTH && maps->yo < HEIGHT)
    {
    	if (wall)
			mlx_put_pixel(display->g_img, maps->xo, maps->yo, get_rgba(0,80,100));
		else
			mlx_put_pixel(display->g_img, maps->xo, maps->yo, get_rgba(100,100,100));
        j = 1;
		maps->yo = (maps->y * display->maps->y_coeff);
		while(j < display->maps->y_coeff - 1 && maps->xo < WIDTH && maps->yo < HEIGHT)
		{
			if (wall)
				mlx_put_pixel(display->g_img, maps->xo, maps->yo, get_rgba(0,80,100));
			else
				mlx_put_pixel(display->g_img, maps->xo, maps->yo, get_rgba(100,100,100));
			maps->yo++;
			j++;
		}
		maps->xo++;
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
	maps->xo = 0;
	maps->yo = 0;
	while (maps->y < maps->max_y)
	{
		maps->x = 0;
		maps->xo = 0;
		while (maps->x < maps->max_x)
		{
			maps->yo = (maps->y * display->maps->y_coeff);
			maps->xo = (maps->x * display->maps->x_coeff);
			if (map[maps->y][maps->x] == '1')
				draw_cube(display, true);
			else
				draw_cube(display, false);
			maps->x++;
		}
		maps->y++;
	}
}

int	main(int argc, char **argv)
{
	t_display	*display;
	(void)		argc;
	(void)		argv;

	display = ft_calloc(sizeof(t_display), 1);
	if (!display)
		return (0);
	allocate_memory(display);
	// check_input(argc, argv, display);
	init_display(argc, argv, display);
	cub3d(argv, display);
	clean_up(display);
	return (0);
}
