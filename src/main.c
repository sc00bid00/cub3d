/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:59:25 by lsordo            #+#    #+#             */
/*   Updated: 2023/05/10 11:16:55 by kczichow         ###   ########.fr       */
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
	// draw_line(display, display->pos->x, display->pos->y);
	calc_rays(display, display->pos, display->ray, display->wall);
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
		display->pos->a -=0.05;
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
		display->pos->a +=0.05;
		if(display->pos->a > 2 * M_PI)
			display->pos->a -= 2 * M_PI;
		display->pos->dx = cos(display->pos->a) * 5;
		display->pos->dy = sin(display->pos->a) * 5;
		// display->pos->x += display->pos->dx;
		// display->pos->x += 5.0;
	}
	drawMap2D(display);
	// draw_line(display, display->pos->x, display->pos->y);
	draw_player(display);
	calc_rays(display, display->pos, display->ray, display->wall);
}

/* uses pythagoran theorem to return distance from player */
/* must be adjusted to avoid fishbowl effect */
float 	dist(t_pos *pos, float bx, float by, float ang)
{
	return (sqrt((bx - pos->x) * (bx - pos->x)) + (by - pos->y) * (by - pos->y));
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
	draw_line_bresenham(display, posx, posy, x_end, y_end, 270);
}

void	draw_player(t_display *display)
{
	my_put_pixel(display);
}

void	my_put_pixel(t_display *display)
{
	if (display->pos->y > HEIGHT)
		display->pos->y = HEIGHT - 1;
	if (display->pos->y < 0)
		display->pos->y = 0;
	if (display->pos->x > WIDTH)
		display->pos->x = WIDTH - 1;
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
