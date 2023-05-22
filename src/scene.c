/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:28:32 by kczichow          #+#    #+#             */
/*   Updated: 2023/05/22 18:33:49 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*	remove fisheye effet with cosinus, calculate line height using distance, */
/*	calculate offset from middle horizontal line */
void	calculate_3D_param(t_display *d, t_wall *wall, t_pos *pos, t_ray *ray)
{
	wall->dis_t = ray->dis_t * HEIGHT/d->maps->height_mm;
	wall->ca = pos->a - ray->a;
	if (wall->ca < 0)
		wall->ca += 2 * M_PI;
	if (wall->ca > 2 * M_PI)
		wall->ca -= 2 * M_PI;
	wall->dis_t = wall->dis_t * cos(wall->ca);
	wall->line_h = (HEIGHT * d->maps->map_s * 4) / (wall->dis_t);
	if (wall->line_h > HEIGHT)
		wall->line_h = HEIGHT;
	wall->line_off = (HEIGHT - wall->line_h) / 2;
}

// void	draw_wall(t_display *display)
// {
	
// }



void	draw_column(t_display *display, t_ray *ray, t_wall *wall, t_maps *maps)
{
	int i;
	int j;
	(void) maps;
	i = 0;
	j = 0;
	// int skyline = HEIGHT / 2;
	while (i <= WIDTH / ray->ray_max)
	{
		j = 0;
		wall->y0 = 0;
		int wall_height = 640 / wall->line_off * (WIDTH / 2) * tan(1.0472 / 2);

		
		while (j < HEIGHT-1 && wall->x0 >=0 && wall->x0 <= WIDTH)
		{
			// if (skyline - wall_height / 2 + j < 0)
			// 	j = wall_height / 2 - skyline;
			// if (skyline - wall_height / 2 + j > HEIGHT)
			// 	break ;
			if (wall->y0 >= wall->line_off && wall->y0 <= (HEIGHT - wall->line_off))
			{
				// if (ray->hx - (int) ray->hx == 0) {
				// 	pixel = img_pixel(ray->hy - (int)ray->hy, ((double)j / (double)wall_height), display->tex[NO]);
				// } else {
				// 	pixel = img_pixel(ray->hx- (int)ray->hx, ((double)j / (double)wall_height), display->tex[NO]);
				// }
				int pixel = 0;
				if (ray->x0 - (int) ray->x0 == 0) {
					pixel = img_pixel(ray->hy - (int)ray->hy, ((double)j / (double)wall_height), display->tex[NO]);
				} else {
					pixel = img_pixel(ray->hx - (int)ray->hx, ((double)j / (double)wall_height), display->tex[NO]);
				}		
				
				// int	offset = display->tex[NO]->width * ray->hy - (int)ray->hx;
				// uint32_t	pixel = (uint32_t) display->tex[NO] + offset + display->tex[NO]->width * j; 
				// draw_wall(display);
				// mlx_put_pixel
				my_put_pixel(display->s_img, wall->x0, wall->y0, pixel );
			}
			wall->y0++;
			j++;
		}
		// printf("vx, vy is %f %f\n", ray->vx, ray->vy);
		// printf("hx, hy is %f %f\n", ray->hx, ray->hy);
		wall->x0++;
		i++;
	}
}
