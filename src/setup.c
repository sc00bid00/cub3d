/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:50:58 by kczichow          #+#    #+#             */
/*   Updated: 2023/05/22 09:20:59 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*	init map and scale minimap */
void	setup_maps(t_maps *maps, t_pdata *pdata)
{
	ft_bzero(maps, sizeof(t_maps));
	maps->max_x = pdata->num_cols - 1;
	maps->max_y = pdata->num_rows;
	if (maps->max_x >= maps->max_y)
	{
		maps->map_s = WIDTH / 5 / maps->max_x;
		maps->width_mm = maps->map_s * maps->max_x;
		maps->height_mm = maps->width_mm * maps->max_y / maps->max_x;
	}
	else
	{
		maps->map_s = HEIGHT / 5 / maps->max_y;
		maps->height_mm = maps->map_s * maps->max_y;
		maps->width_mm = maps->height_mm * maps->max_x / maps->max_y;
	}
}

void	setup_pos(t_pos *pos, t_pdata *pdata, t_maps *maps)
{
	ft_bzero(pos, sizeof(t_pos));
	pos->x = pdata->player_positionxy[0] * maps->map_s;
	pos->y = pdata->player_positionxy[1] * maps->map_s;
	pos->a = pdata->player_directionrad;
	// pos->a = 1.0472; // angle expressed in radians
	pos->dx = cos(pos->a) * 5;
	pos->dy = sin(pos->a) * 5; 
}

void	setup_rays(t_ray *ray)
{
	ft_bzero(ray, sizeof(t_ray));
	ray->dis_h = 10000;
	ray->dis_v = 10000;
	ray->ray_max = 320;
}

void	setup_wall(t_wall *wall)
{
	ft_bzero(wall, sizeof(t_wall));
}

/* init window layers for floor/ceiling, scene and minimap */
void	setup_windows(t_display *display)
{
		display->f_c_img = mlx_new_image(display->mlx, WIDTH, HEIGHT);
		display->s_img = mlx_new_image(display->mlx, WIDTH, HEIGHT);
		display->mm_img = mlx_new_image(display->mlx, display->maps->width_mm, \
		display->maps->height_mm);
		memset_window(display);
}

/* path to be updated with values from file */
void	load_tex(t_display *display, t_pdata *pdata)
{
	(void) pdata;
	// display->tex[NO] = mlx_load_png(pdata->textures_path[NO]);
	// display->tex[SO] = mlx_load_png(pdata->textures_path[SO]);
	// display->tex[WE] = mlx_load_png(pdata->textures_path[WE]);
	// display->tex[EA] = mlx_load_png(pdata->textures_path[EA]);
	display->tex[NO] = mlx_load_png("./textures/redbrick.png");
	display->tex[SO] = mlx_load_png("./textures/redbrick.png");
	display->tex[WE] = mlx_load_png("./textures/redbrick.png");
	display->tex[EA] = mlx_load_png("./textures/redbrick.png");
}

void	setup_display(t_display *display)
{
	setup_maps(display->maps, display->pdata);
	setup_pos(display->pos, display->pdata, display->maps);
	setup_rays(display->ray);
	setup_wall(display->wall);
	setup_windows(display);
	load_tex(display, display->pdata);
}