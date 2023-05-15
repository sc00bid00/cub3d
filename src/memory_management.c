/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:05:10 by kczichow          #+#    #+#             */
/*   Updated: 2023/05/15 16:30:01 by kczichow         ###   ########.fr       */
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
	display->wall = ft_calloc(1, sizeof(t_wall));
	if (!display->wall)
		clean_up(display);
}


void	read_data(t_display *display)
{
	display->pos->x = display->pdata->player_positionxy[0] * display->maps->map_sx;
	display->pos->y = display->pdata->player_positionxy[1] * display->maps->map_sy;
	display->pos->a = display->pdata->player_directionrad;
	display->maps->max_x = display->pdata->num_cols - 1;
	display->maps->max_y = display->pdata->num_rows;
}
/*	initialize mlx, map and player */
void	scale_minimap(t_display *display)
{
	if (display->maps->max_x >= display->maps->max_y)
	{
		display->maps->map_s = WIDTH / 5 / display->maps->max_x;
		// display->maps->map_sy = display->maps->map_sx  display->maps->max_y;
		display->maps->width_mm = display->maps->map_sx * display->maps->max_x;
		display->maps->height_mm = display->maps->width_mm * display->maps->max_y / display->maps->max_x;
	}
	else
	{
		display->maps->map_s = HEIGHT / 5 / display->maps->max_y;
		// display->maps->map_sx = WIDTH / 5 / display->maps->max_x;
		display->maps->height_mm = display->maps->map_sy * display->maps->max_y;
		display->maps->width_mm = display->maps->height_mm * display->maps->max_x / display->maps->max_y;
	}
	display->maps->x_coeff = display->maps->map_sx;
	display->maps->y_coeff = display->maps->map_sy;
	// printf("map sy is %d\n", display->maps->map_sy);
	// printf("map sx is %d\n", display->maps->map_sx);
	// exit (0);
}

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
	display->maps->max_x = 9;
	display->maps->max_y = 8;
	

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
	display->ray->atan	= 0;
	display->ray->ntan	= 0;
	display->ray->ray_max = 1000;

	display->wall->dis_t = 0;
	display->wall->ca = 0;
	display->wall->line_h = 0;
	display->wall->line_off = 0;
	display->wall->count = 0;
	display->wall->x0 = 0;
	display->wall->y0 = 0;
	display->wall->shading = 0;
	display->wall->pos_x = 0;
	display->wall->pos_y = 0;
	read_data(display);
	scale_minimap(display);
}


/*	free all allocated memory */

int	clean_up(t_display *display)
{
	tmp_freedisplay(display);
	if (display->pos)
		free (display->pos);
	if (display->maps)
		free (display->maps);
	if (display->ray)
		free (display->ray);
	if (display->wall)
		free (display->wall);
	if (display->mlx)
	{
		mlx_delete_image(display->mlx, display->mm_img);
		mlx_terminate(display->mlx);
	}
	if (display)
		free (display);
	// system ("leaks cub3D");
	return (0);
}