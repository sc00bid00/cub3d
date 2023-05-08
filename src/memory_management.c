/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:05:10 by kczichow          #+#    #+#             */
/*   Updated: 2023/05/05 15:35:04 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/* allocate memory for all structs within t_image struct */

void allocate_memory(t_display *display)
{
	display->pos = ft_calloc(1, sizeof(t_pos));
	if (!display->pos)
		clean_up(display);
	display->maps = ft_calloc(1, sizeof(t_maps));
	if (!display->maps)
		clean_up(display);
	display->rays = ft_calloc(1, sizeof(t_rays));
	if (!display->rays)
		clean_up(display);
}

/*	initialize mlx, map and player */

void	init_display(int argc, char **argv, t_display *display)
{
	(void)		argc;
	(void)		argv;
	display->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
		if (!display->mlx)
			exit(EXIT_FAILURE);
	display->pos->x = 300.0;
	display->pos->y = 300.0;
	display->pos->a = 1;
	display->pos->dx = cos(display->pos->a) * 5;
	display->pos->dy = sin(display->pos->a) * 5; 
	display->pos->x0 = 0;
	display->pos->y0 = 0;
	display->pos->a0 = 0;

	display->maps->x = 0;
	display->maps->y = 0;
	display->maps->x0 = 0;
	display->maps->y0 = 0;
	display->maps->max_x = 8;
	display->maps->max_y = 8;
	display->maps->x_coeff = mapS;
	display->maps->y_coeff = mapS;
	// display->maps->x_coeff = WIDTH / display->maps->max_x;
	// display->maps->y_coeff = HEIGHT / display->maps->max_y;

	display->rays->mx = 0;
	display->rays->my = 0;
	display->rays->x = 0;
	display->rays->y = 0;
	display->rays->a = 0;
	display->rays->x0 =	0;
	display->rays->y0 = 0;
	display->rays->x_off = 0;
	display->rays->y_off = 0;
}


/*	free all allocated memory */

int	clean_up(t_display *display)
{
	if (display->pos)
		free (display->pos);
	if (display->maps)
		free (display->maps);
	if (display->rays)
		free (display->rays);
	if (display->mlx)
	{
		mlx_delete_image(display->mlx, display->g_img);
		mlx_terminate(display->mlx);
	}
	if (display)
		free (display);
	// system ("leaks cub3D");
	return (0);
}