/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:59:25 by lsordo            #+#    #+#             */
/*   Updated: 2023/05/05 15:56:31 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>


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
	draw_line(display, display->pos->x, display->pos->y);
	draw_rays(display);
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

/*	keys W and S to move forward / backward, keys A and D to rotate */
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
	draw_line(display, display->pos->x, display->pos->y);
	draw_player(display);
	draw_rays(display);
}

/*	mapS defined as 64 (pixel cube size) */
void	draw_rays(t_display *display)
{
	// find horizontal intersections
	
	int count;
	int r;
	float atan;

	display->rays->a = display->pos->a;
	for (r = 0; r < 1; r++)
	{
		count = 0;
		atan = -1 / tan (display->rays->a);
		// ray facing upwards
		if (display->rays->a > M_PI)
		{
			// substracts 1 to make the point part of the cube above the line
			// and not on the line;
			display->rays->y0 = ((int) (display->pos->y / mapS) * mapS) - 0.0001;
			display->rays->x0 = display->pos->x + ((display->pos->y - display->rays->y0) / tan(display->rays->a));
			// printf("ray x value is %f\n", display->rays->x0);
			// printf("display->rays->y0 %f\n", display->rays->y0);
			// printf("display->pos->y is %f\n", display->pos->y);
			// printf("tan value is %f\n", tan(display->rays->a));
			display->rays->y_off = mapS * -1;
			display->rays->x_off = mapS * atan;
			printf("facing up\n");
		}	
		// ray facing downwards
		else if (display->rays->a < M_PI && display->rays->a > 0)
		{
			// substracts 1 to make the point part of the cube above the line
			// and not on the line; ay
			display->rays->y0 = ((int) (display->pos->y / mapS) * mapS) + mapS;
			display->rays->x0 = display->pos->x + (display->pos->y - display->rays->y0) * atan;
			display->rays->y_off = mapS;
			display->rays->x_off = mapS * atan;
			printf("facing down\n");
		}
		else if (display->rays->a == M_PI || display->rays->a == 0)
		{
			display->rays->x0 = display->pos->x;
			display->rays->y0 = display->pos->y;
			count = display->maps->max_y;
			printf("facing sidways\n");
		}
		while (count < display->maps->max_y)
		{
			display->rays->mx = (int) display->rays->x0 / mapS;
			display->rays->my = (int) display->rays->y0 / mapS;
			// printf("x value is %d\n", display->rays->mx);
			// printf("y value is %d\n", display->rays->my);
			if (display->rays->mx < display->maps->max_x && display->rays->my < display->maps->max_y)
			{
				if (map[display->rays->mx][display->rays->my] == '1')
				{
					printf("hit wall at coordinate[%d][%d]\n", display->rays->mx, display->rays->my);
					// exit(0);
					count = display->maps->max_y;
				}
				else
				{
					printf("no wall at coordinate[%d][%d]\n", display->rays->mx, display->rays->my);
					display->rays->y0 += display->rays->y_off;
					display->rays->x0 += display->rays->x_off;
					count++;
				}
			}	
		}
		if (display->pos->x > 0 && display->pos->x < WIDTH && display->rays->x0 > 0 && display->rays->x0 < WIDTH && display->pos->y > 0 && display->pos->y < HEIGHT && display->rays->y0 > 0 && display->rays->y0 < HEIGHT)
		draw_line_bresenham(display, display->pos->x, display->pos->y, display->rays->x0, display->rays->y0);
	}
}


/* specify line details */
void	draw_line(t_display *display, float posx, float posy)
{
	float	x_end;
	float	y_end;
	int		length;

	length = 20;
	x_end = posx + length * cos(display->pos->a);
	y_end = posy + length * sin(display->pos->a);
	draw_line_bresenham(display, posx, posy, x_end, y_end);
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
    while (i < display->maps->x_coeff - 1 && maps->x0 < WIDTH && maps->y0 < HEIGHT)
    {
    	if (wall)
			mlx_put_pixel(display->g_img, maps->x0, maps->y0, get_rgba(0,80,100));
		else
			mlx_put_pixel(display->g_img, maps->x0, maps->y0, get_rgba(100,100,100));
        j = 1;
		maps->y0 = (maps->y * display->maps->y_coeff);
		while(j < display->maps->y_coeff - 1 && maps->x0 < WIDTH && maps->y0 < HEIGHT)
		{
			if (wall)
				mlx_put_pixel(display->g_img, maps->x0, maps->y0, get_rgba(0,80,100));
			else
				mlx_put_pixel(display->g_img, maps->x0, maps->y0, get_rgba(100,100,100));
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
