/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:05:10 by kczichow          #+#    #+#             */
/*   Updated: 2023/05/03 16:12:59 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/* ALLOCATE_MEMORY
* ------------------
* allocate memory for all structs within t_image struct
*/

void allocate_memory(t_display *display)
{
	display->pos = ft_calloc(1, sizeof(t_pos));
	if (!display->pos)
		clean_up(display);
	display->maps = ft_calloc(1, sizeof(t_maps));
	if (!display->maps)
		clean_up(display);
}

/*	INIT_SET
*	---------
*	initialize mlx, color and parameters.
*/
void	init_display(int argc, char **argv, t_display *display)
{
	(void)		argc;
	(void)		argv;
	display->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
		if (!display->mlx)
			exit(EXIT_FAILURE);
	display->pos->x = 300.0;
	display->pos->y = 300.0;
	display->maps->x = 0;
	display->maps->y = 0;
	display->maps->xo = 0;
	display->maps->yo = 0;
	display->maps->map_x = 8; //number of columns in map;
	display->maps->map_y = 8; //number of lines in map;
	display->maps->map_s = display->maps->map_x * display->maps->map_y; //total number of tiles in map
	display->maps->x_coeff = WIDTH / display->maps->map_x;
	display->maps->y_coeff = HEIGHT / display->maps->map_y;
}


/* CLEAN_UP
* ------------------
* free all allocated memory
*/

int	clean_up(t_display *display)
{
	if (display->pos)
		free (display->pos);
	if (display->maps)
		free (display->maps);
	// if (display->color)
	// 	free (display->color);
	// if (display->mlx)
	{
		mlx_delete_image(display->mlx, display->g_img);
		mlx_terminate(display->mlx);
	}
	if (display)
		free (display);
	system ("leaks cub3D");
	return (0);
}