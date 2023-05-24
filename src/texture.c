/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:08:58 by kczichow          #+#    #+#             */
/*   Updated: 2023/05/23 16:33:21 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/* vertical walls: wall_dir  = 1	*/
void	get_wall_dir(t_display *display)
{
	if (display->wall->dir == 1)
	{
		if (display->ray->x_off <= 0)
		{
			display->wall->offset_x = 1200 / display->wall->line_h * sin(display->ray->a);
			display->wall->texture = display->tex[WE];
		}
		else if (display->ray->x_off > 0)
		{
			display->wall->offset_x = 1200 / display->wall->line_h * sin(display->ray->a);
			display->wall->texture = display->tex[EA];
		}	
	}
	if (display->wall->dir == 0)
	{
		if (display->ray->y_off <= 0)
		{
			display->wall->offset_x = 1200 / display->wall->line_h * cos(display->ray->a);
			display->wall->texture = display->tex[NO];
		}
		else if (display->ray->y_off > 0)
		{
			display->wall->texture = display->tex[SO];
			display->wall->offset_x = 1200 / display->wall->line_h * cos(display->ray->a);
		}
	}
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
	display->tex[SO] = mlx_load_png("./textures/greystone.png");
	display->tex[WE] = mlx_load_png("./textures/bluestone.png");
	display->tex[EA] = mlx_load_png("./textures/walkstone.png");
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
   	// y = (int)(y_p * tex->height);
	y = (int)(y_p * tex->height) * (tex->width);
    ptr = &tex->pixels[(int)(x * 4 + y * 4)];
    return (get_color(ptr));
}
