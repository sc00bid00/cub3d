/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:08:58 by kczichow          #+#    #+#             */
/*   Updated: 2023/05/25 12:56:05 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	reset_offset(t_wall *wall)
{
	while (wall->offset_x < 0)
	{
		wall->offset_x += 1;
		printf(" ");
	}
	while (wall->offset_x > 1)
		wall->offset_x -= 1;
}

/* vertical walls: wall_dir  = 1	*/
void	get_wall_dir(t_display *display)
{
	if (display->wall->dir == 1)
	{
		if (display->ray->x_off < 0)
		{
			display->wall->offset_x = display->wall->line_w / display->wall->line_h * sin(display->ray->a);
			reset_offset(display->wall);
			display->wall->texture = display->tex[WE];
		}
		else if (display->ray->x_off > 0)
		{
			display->wall->offset_x = display->wall->line_w / display->wall->line_h * sin(display->ray->a);
			reset_offset(display->wall);
			display->wall->texture = display->tex[EA];
		}
	}
	if (display->wall->dir == 0)
	{
		if (display->ray->y_off < 0)
		{
			display->wall->offset_x = display->wall->line_w / display->wall->line_h * cos(display->ray->a);
			reset_offset(display->wall);
			display->wall->texture = display->tex[NO];
		}
		else if (display->ray->y_off > 0)
		{
			display->wall->offset_x = display->wall->line_w / display->wall->line_h * cos(display->ray->a);
			reset_offset(display->wall);
			display->wall->texture = display->tex[SO];
		}
	}
}

/* path to be updated with values from file */
void	load_tex(t_display *display, t_pdata *pdata)
{
	display->tex[NO] = mlx_load_png(pdata->textures_path[NO]);
	display->tex[SO] = mlx_load_png(pdata->textures_path[SO]);
	display->tex[WE] = mlx_load_png(pdata->textures_path[WE]);
	display->tex[EA] = mlx_load_png(pdata->textures_path[EA]);
}

int get_color(uint8_t *start)
{
    int color;
    int i;

    i = 0;
    color = 0;
    while (i < 4)
    {
        color = color << 8;
        color = color | *(start + i);
        i++;
    }
    return (color);
}

int img_pixel(double x_p, double y_p, mlx_texture_t *tex)
{
	uint8_t *ptr;
	int     x;
    int     y;

    x = (int)(x_p * tex->width);
	y = (int)(y_p * tex->height) * (tex->width);
    ptr = &tex->pixels[(int)(x * 4 + y * 4)];
    return (get_color(ptr));
}
