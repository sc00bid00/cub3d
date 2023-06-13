/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:59:25 by lsordo            #+#    #+#             */
/*   Updated: 2023/06/13 12:59:58 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*	CUB3D
*	--------
*	create image, link hooks and place the image within the window.
*	It calls the drawing function.
*/

void	cub3d(t_display *display)
{
	setup_windows(display);
	draw_minimap(display);
	render(display, display->pos, display->ray, display->wall);
	draw_floor_ceiling(display);
	image_to_window(display);
	mlx_key_hook(display->mlx, &my_keyhook, display);
	mlx_loop_hook(display->mlx, &my_hook, display);
	// mlx_scroll_hook(display->mlx, &my_scrollhook, display);
	mlx_loop(display->mlx);
	return ;
}


/* uses pythagoran theorem to return distance from player */
/* must be adjusted to avoid fishbowl effect */
double 	dist(t_pos *pos, double bx, double by, double ang)
{
	(void) ang;
	return (sqrt((bx - pos->x) * (bx - pos->x) + (by - pos->y) * (by - pos->y)));
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

int	main(int argc, char **argv)
{
	t_display	*display;

	display = ft_calloc(1, sizeof(t_display));
	if (!display)
		return (put_err(ERR_MEMORY));
	if (chk_args(argc, argv))
	{
		if (init_pdata(display, argv) && get_data(display->pdata))
		{
			allocate_memory(display);
			setup_display(display);
			cub3d(display);
		}
	}
	clean_up(display);
	return (0);
}
