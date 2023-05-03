/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:59:25 by lsordo            #+#    #+#             */
/*   Updated: 2023/05/03 16:43:51 by kczichow         ###   ########.fr       */
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
		display->pos->y -= 5.0;
	}
	if (mlx_is_key_down(display->mlx, MLX_KEY_S))
	{
		ft_memset(display->g_img->pixels, COLOR, display->g_img->width \
			* display->g_img->height * sizeof(int32_t));
		display->pos->y += 5.0;
	}
	if (mlx_is_key_down(display->mlx, MLX_KEY_A))
	{
		ft_memset(display->g_img->pixels, COLOR, display->g_img->width \
			* display->g_img->height * sizeof(int32_t));
		display->pos->x -= 5.0;
	}
	if (mlx_is_key_down(display->mlx, MLX_KEY_D))
	{
		ft_memset(display->g_img->pixels, COLOR, display->g_img->width \
			* display->g_img->height * sizeof(int32_t));
		display->pos->x += 5.0;
	}
	drawMap2D(display);
	draw_player(display);
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
    "10100001",
    "10100001",
    "10000001",
    "10111101",
    "10000001",
    "11111111"
};

void init_map_values(t_maps *maps)
{
	maps->x = 0;
	maps->y = 0;
	maps->xo = 0;
	maps->yo = 0;
}

void	draw_map(t_display *display, bool wall)
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

void drawMap2D(t_display *display)
{
	t_maps	*maps;
	int i;
	int j;

	maps = display->maps;
	i = 0;
	j = 0;
	init_map_values(maps);
	while (maps->y < mapY)
	{
		maps->x = 0;
		maps->xo = 0;
		while (maps->x < mapX)
		{
			maps->yo = (maps->y * display->maps->y_coeff);
			maps->xo = (maps->x * display->maps->x_coeff);
			if (map[maps->y][maps->x] == '1')
				draw_map(display, true);
			else
				draw_map(display, false);
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