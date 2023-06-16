/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:08:58 by kczichow          #+#    #+#             */
/*   Updated: 2023/06/16 12:41:16 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/* vertical walls: wall_dir  = 1	*/
void	get_wall_dir(t_display *display)
{
	if (display->wall->dir == 1)
	{
		if (display->ray->x_off < 0)
			display->wall->texture = display->tex[WE];
		else if (display->ray->x_off > 0)
			display->wall->texture = display->tex[EA];
		display->wall->offset_x = (double)((int)(display->ray->y0 * COEFF) \
			% (display->maps->map_s * COEFF) / \
			((double) display->maps->map_s * COEFF));
	}
	if (display->wall->dir == 0)
	{
		if (display->ray->y_off < 0)
			display->wall->texture = display->tex[NO];
		else if (display->ray->y_off > 0)
			display->wall->texture = display->tex[SO];
		display->wall->offset_x = (double)((int)(display->ray->x0 * COEFF) \
			% (display->maps->map_s * COEFF) / \
			((double) display->maps->map_s * COEFF));
	}
	reset_offset(display->wall);
}

/* path to be updated with values from file */
void	load_tex(t_display *display, t_pdata *pdata)
{
	display->tex[NO] = mlx_load_png(pdata->textures_path[NO]);
	display->tex[SO] = mlx_load_png(pdata->textures_path[SO]);
	display->tex[WE] = mlx_load_png(pdata->textures_path[WE]);
	display->tex[EA] = mlx_load_png(pdata->textures_path[EA]);
}

int	get_color(uint8_t *start)
{
	int	color;
	int	i;

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

int	img_pixel(double x_p, double y_p, mlx_texture_t *tex)
{
	uint8_t	*ptr;
	int		x;
	int		y;

	x = (int)(x_p * tex->width);
	y = (int)(y_p * tex->height) * (tex->width);
	ptr = &tex->pixels[(int)(x * 4 + y * 4)];
	return (get_color(ptr));
}

/*	GET_RGBA
*	----------
*	Function combines four individual channel bytes into a single integer using
*	bit-shifting. The last byte is for transparency and always set to 255.
*/
uint32_t	get_rgba(uint8_t red, uint8_t green, uint8_t blue)
{
	return ((uint32_t)(red << 24 | green << 16 | blue << 8 | 255));
}
