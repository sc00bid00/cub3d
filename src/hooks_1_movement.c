/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_1_movement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:01:53 by kczichow          #+#    #+#             */
/*   Updated: 2023/06/15 17:53:07 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	border(t_display *d, double y, double x)
{
	y = (int) y;
	x = (int) x;
	if (y < (d->pdata->num_rows - 1) && y >= 1 && \
		x < (d->pdata->num_cols -2) && x >= 1 && \
		!collision(d, y, x))
		return (0);
	return (1);
}

/*	for either direction, function first checks if surrounding wall is hit */
void	move_left_right(t_display *d)
{
	double	tmp_x;
	double	tmp_y;

	tmp_x = d->pos->x;
	tmp_y = d->pos->y;
	if (mlx_is_key_down(d->mlx, MLX_KEY_A))
	{
		tmp_x += d->pos->dy;
		tmp_y -= d->pos->dx;
		if (!border(d, tmp_y / d->maps->map_s, tmp_x / d->maps->map_s))
		{
			d->pos->x = tmp_x;
			d->pos->y = tmp_y;
		}
	}
	else if (mlx_is_key_down(d->mlx, MLX_KEY_D))
	{
		tmp_x -= d->pos->dy;
		tmp_y += d->pos->dx;
		if (!border(d, tmp_y / d->maps->map_s, tmp_x / d->maps->map_s))
		{
			d->pos->x = tmp_x;
			d->pos->y = tmp_y;
		}
	}
}

void	move_up_down(t_display	*d)
{
	double	tmp_x;
	double	tmp_y;

	tmp_x = d->pos->x;
	tmp_y = d->pos->y;
	if (mlx_is_key_down(d->mlx, MLX_KEY_W))
	{
		tmp_x += d->pos->dx;
		tmp_y += d->pos->dy;
		if (!border(d, tmp_y / d->maps->map_s, tmp_x / d->maps->map_s))
		{
			d->pos->x = tmp_x;
			d->pos->y = tmp_y;
		}
	}
	else if (mlx_is_key_down(d->mlx, MLX_KEY_S))
	{
		tmp_x -= d->pos->dx;
		tmp_y -= d->pos->dy;
		if (!border(d, tmp_y / d->maps->map_s, tmp_x / d->maps->map_s))
		{
			d->pos->x = tmp_x;
			d->pos->y = tmp_y;
		}
	}
}

void	rotate(t_display *display)
{
	if (mlx_is_key_down(display->mlx, MLX_KEY_LEFT))
	{
		display->pos->a -= 0.05;
		display->pos->dx = cos(display->pos->a) * 5;
		display->pos->dy = sin(display->pos->a) * 5;
	}
	else if (mlx_is_key_down(display->mlx, MLX_KEY_RIGHT))
	{
		display->pos->a += 0.05;
		display->pos->dx = cos(display->pos->a) * 5;
		display->pos->dy = sin(display->pos->a) * 5;
	}
	reset_player_angle(display->pos);
}

/*	keys W and S to move forward / backward, keys A and D to move sidewards */
/*	arrow keys to rotate */
void	my_hook(void *param)
{
	t_display	*display;

	display = param;
	move_up_down(display);
	move_left_right(display);
	rotate(display);
	reset_ray_angle(display);
	memset_window(display);
	draw_floor_ceiling(display);
	draw_minimap(display);
	render(display, display->pos, display->ray, display->wall);
	return ;
}
