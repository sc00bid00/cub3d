/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:05:10 by kczichow          #+#    #+#             */
/*   Updated: 2023/05/09 15:31:34 by kczichow         ###   ########.fr       */
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
	display->ray = ft_calloc(1, sizeof(t_ray));
	if (!display->ray)
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
	display->pos->x = 96.0;
	display->pos->y = 224.0;
	display->pos->a = 1.0472; // angle expressed in radians
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

	display->ray->x = 0;
	display->ray->y = 0;
	display->ray->a = 0;
	display->ray->x0 =	0;
	display->ray->y0 = 0;
	display->ray->x_off = 0;
	display->ray->y_off = 0;
	display->ray->hx = 0;
	display->ray->hy = 0;
	display->ray->vx = 0;
	display->ray->vy = 0;
	display->ray->dis_h = 10000;
	display->ray->dis_v = 10000;
}


/*	free all allocated memory */

int	clean_up(t_display *display)
{
	if (display->pos)
		free (display->pos);
	if (display->maps)
		free (display->maps);
	if (display->ray)
		free (display->ray);
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