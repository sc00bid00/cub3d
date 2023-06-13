/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:59:25 by lsordo            #+#    #+#             */
/*   Updated: 2023/06/13 14:45:20 by kczichow         ###   ########.fr       */
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
	mlx_loop(display->mlx);
	return ;
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
