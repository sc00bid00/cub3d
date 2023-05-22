/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:08:58 by kczichow          #+#    #+#             */
/*   Updated: 2023/05/22 18:39:48 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/* vertical walls: wall_dir  = 1*/
void	get_wall_dir(t_display *display)
{
	char	wall_tex;

	if (display->wall->dir == 1)
	{
		if (display->ray->x_off <= 0)
		{
			wall_tex = 'W';
			display->wall->shading = get_rgba(0, 133, 120);
		}
		else if (display->ray->x_off > 0)
		{
			wall_tex = 'E';
			display->wall->shading = get_rgba(0, 89, 79);
		}
	}
	if (display->wall->dir == 0)
	{
		if (display->ray->y_off <= 0)
		{
			wall_tex = 'N';
			display->wall->shading = get_rgba(0, 0, 0);
		}
		else if (display->ray->y_off > 0)
		{
			wall_tex = 'S';
			display->wall->shading = get_rgba(0, 0, 0);
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
	display->tex[SO] = mlx_load_png("./textures/redbrick.png");
	display->tex[WE] = mlx_load_png("./textures/redbrick.png");
	display->tex[EA] = mlx_load_png("./textures/redbrick.png");
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
