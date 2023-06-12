/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:08:58 by kczichow          #+#    #+#             */
/*   Updated: 2023/06/12 13:05:03 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	reset_offset(t_wall *wall)
{
	while (wall->offset_x < 0)
		wall->offset_x += 1;
	while (wall->offset_x > 1)
		wall->offset_x -= 1;
}

// /* vertical walls: wall_dir  = 1	*/
// void	get_wall_dir(t_display *display)
// {
// 	if (display->wall->dir == 1)
// 	{
// 		display->wall->offset_x = display->wall->line_w / display->wall->line_h * sin(display->ray->a);
// 		if (display->ray->x_off < 0)
// 			display->wall->texture = display->tex[WE];
// 		else if (display->ray->x_off > 0)
// 			display->wall->texture = display->tex[EA];
// 	}
// 	if (display->wall->dir == 0)
// 	{
// 		display->wall->offset_x = display->wall->line_w / display->wall->line_h * cos(display->ray->a);
// 		if (display->ray->y_off < 0)
// 			display->wall->texture = display->tex[NO];
// 		else if (display->ray->y_off > 0)
// 			display->wall->texture = display->tex[SO];
// 	}
// 	double player_offset = display->pos->x - (int)display->pos->x;
// 	// reset_offset(display->wall);
// 	display->wall->offset_x = player_offset - display->wall->offset_x;
// 	reset_offset(display->wall);
// }

/* vertical walls: wall_dir  = 1	*/
void	get_wall_dir(t_display *display)
{
	// display->wall->new_wall = 1;
	if (display->wall->dir == 1)
	{
		display->wall->offset_x = (display->wall->line_w / display->wall->line_h - display->pos->x / WIDTH) * sin(display->ray->a);
		if (display->ray->x_off < 0)
			display->wall->texture = display->tex[WE];
		else if (display->ray->x_off > 0)
			display->wall->texture = display->tex[EA];
	}
	if (display->wall->dir == 0)
	{
		display->wall->offset_x = (display->wall->line_w / display->wall->line_h - display->pos->y / WIDTH) * cos(display->ray->a) ;
		if (display->ray->y_off < 0)
			display->wall->texture = display->tex[NO];
		else if (display->ray->y_off > 0)
			display->wall->texture = display->tex[SO];
	}
	if (display->wall->texture == display->wall->old_tex)
		display->wall->new_wall = 0;
	display->wall->old_tex = display->wall->texture;
	// if (display->wall->new_wall == 1)
	// {
	// 	display->wall->offset_x = 0;
	// }
	// else
	// {
	// 	display->wall->offset_x += 0.5;
	// }
	reset_offset(display->wall);
	printf("DEBUG: offset_x = %.3f\n", display->wall->offset_x);
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
