/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:01:53 by kczichow          #+#    #+#             */
/*   Updated: 2023/05/23 17:02:47 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*	Press esc: clean up function is called: window closes */
void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	mlx_t		*mlx;
	t_display	*display;
	(void) keydata;

	display = param;
	mlx = display->mlx;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
}

/*	keys W and S to move forward / backward, keys A and D to rotate */
void	my_hook(void *param)
{
	t_display	*display;

	display = param;
	if (mlx_is_key_down(display->mlx, MLX_KEY_W))
	{
		display->pos->x += display->pos->dx;
		display->pos->y += display->pos->dy;
	}
	if (mlx_is_key_down(display->mlx, MLX_KEY_S))
	{
		display->pos->x -= display->pos->dx;
		display->pos->y -= display->pos->dy;
	}
	if (mlx_is_key_down(display->mlx, MLX_KEY_A))
	{
		display->pos->a -=0.05;
		display->pos->dx = cos(display->pos->a) * 5;
		display->pos->dy = sin(display->pos->a) * 5;
	}
	if (mlx_is_key_down(display->mlx, MLX_KEY_D))
	{
		display->pos->a +=0.05;
		display->pos->dx = cos(display->pos->a) * 5;
		display->pos->dy = sin(display->pos->a) * 5;
	}
	reset_angles(display);
	memset_window(display);
	draw_floor_ceiling(display);
	draw_minimap(display);
	calc_rays(display, display->pos, display->ray, display->wall);
}
