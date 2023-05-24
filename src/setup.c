/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:50:58 by kczichow          #+#    #+#             */
/*   Updated: 2023/05/23 16:54:01 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	setup_display(t_display *display)
{
	setup_maps(display->maps, display->pdata);
	setup_pos(display->pos, display->pdata, display->maps);
	setup_rays(display->ray);
	setup_wall(display->wall);
	setup_windows(display);
	load_tex(display, display->pdata);
}

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
	pos->fov = 1.0472;
	pos->dx = cos(pos->a) * 5;
	pos->dy = sin(pos->a) * 5;
}

void	setup_rays(t_ray *ray)
{
	ft_bzero(ray, sizeof(t_ray));
	ray->ray_max = 1920;
}

void	setup_wall(t_wall *wall)
{
	ft_bzero(wall, sizeof(t_wall));
}