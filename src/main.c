/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:59:25 by lsordo            #+#    #+#             */
/*   Updated: 2023/05/02 17:03:09 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*	CUB3D
*	--------
*	create image, link hooks and place the image within the window.
*	It calls the drawing function.
*/

void	cub3d(char **argv, t_display *display)
{
	(void)	argv;
	display->g_img = mlx_new_image(display->mlx, WIDTH, HEIGHT);
	memset(display->g_img->pixels, 150, display->g_img->width \
			* display->g_img->height * sizeof(int32_t));
	// mlx_key_hook(display->mlx, &my_keyhook, display);
	// mlx_scroll_hook(display->mlx, &my_scrollhook, display);
	mlx_loop_hook(display->mlx, &my_hook, display);
	// draw_fractal(display);
	draw_player(display);
	mlx_image_to_window(display->mlx, display->g_img, 0, 0);
	mlx_loop(display->mlx);
	return ;
}

void	my_hook(void *param)
{
	t_display	*display;
	
	display = param;
	if (mlx_is_key_down(display->mlx, MLX_KEY_UP))
		display->pos->y -= 50.0;
	if (mlx_is_key_down(display->mlx, MLX_KEY_DOWN))
		display->pos->y += 50.0;
	if (mlx_is_key_down(display->mlx, MLX_KEY_LEFT))
		display->pos->x -= 50.0;
	if (mlx_is_key_down(display->mlx, MLX_KEY_RIGHT))
		display->pos->x += 50.0;
	draw_player(display);
}

void	draw_player(t_display *display)
{
	(void) display;
	display->pos->x = 150.0;
	display->pos->y = 150.0;
	mlx_put_pixel(display->g_img, display->pos->x, display->pos->y, 10);
}

/*	INIT_SET
*	---------
*	initialize mlx, color and parameters.
*/

void	init_set(int argc, char **argv, t_display *display)
{
	(void)		argc;
	(void)		argv;
	display->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
		if (!display->mlx)
			exit(EXIT_FAILURE);
}

/* ALLOCATE_MEMORY
* ------------------
* allocate memory for all structs within t_image struct
*/

void allocate_memory(t_display *display)
{
	display->pos = ft_calloc(1, sizeof(t_pos));
	if (!display->pos)
		return ;
}

int	main(int argc, char **argv)
{
	t_display	*display;
	(void)		argc;
	(void)		argv;

	display = calloc(sizeof(t_display), 1);
	if (!display)
		return (0);
	allocate_memory(display);
	// check_input(argc, argv, display);
	init_set(argc, argv, display);
	cub3d(argv, display);
	// clean_up(display);
	return (0);
}