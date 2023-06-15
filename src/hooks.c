/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:01:53 by kczichow          #+#    #+#             */
/*   Updated: 2023/06/15 10:26:54 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	wall_collision(t_display *d, char **map, int y, int x)
{
	if (y < (d->pdata->num_rows - 1) && y >= 1 && x < (d->pdata->num_cols -2) && x >= 1)
	{
		
	printf("int x is %d int y is %d\n", x, y);
	
	// if (map[(int)(y + 0.1)][(int)(x + 0.1)] != 1
	// 	&& map[(int)(y - 0.1)][(int)(x - 0.1)] != 1
	// 	&& map[(int)(y - 0.1)][(int)(x + 0.1)] != 1
	// 	&& map[(int)(y + 0.1)][(int)(x - 0.1)] != 1)
	if (map[(int)(y)][(int)(x)] != 1)
		return (0);
	else
		return (1);
	}
	return (1);
}

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

void	move_left_right(t_display *display)
{
	double	tmp_x;
	double	tmp_y;
	
	tmp_x = display->pos->x;
	tmp_y = display->pos->y;
	if (mlx_is_key_down(display->mlx, MLX_KEY_A))
	{
		tmp_x += display->pos->dy;
		tmp_y -= display->pos->dx;
		if (!wall_collision(display, display->pdata->map, (int) (tmp_y / display->maps->map_s), (int)(tmp_x / display->maps->map_s)))
		{
			display->pos->x = tmp_x;
			display->pos->y = tmp_y;
		}
	}
	if (mlx_is_key_down(display->mlx, MLX_KEY_D))
	{
		tmp_x -= display->pos->dy;
		tmp_y += display->pos->dx;
		if (!wall_collision(display, display->pdata->map, (int) (tmp_y / display->maps->map_s), (int)(tmp_x / display->maps->map_s)))
		{
			display->pos->x = tmp_x;
			display->pos->y = tmp_y;
		}
	}
}


void	move_up_down(t_display	*display)
{
	double	tmp_x;
	double	tmp_y;
	
	tmp_x = display->pos->x;
	tmp_y = display->pos->y;
	if (mlx_is_key_down(display->mlx, MLX_KEY_W))
	{
		tmp_x += display->pos->dx;
		tmp_y += display->pos->dy;
		if (!wall_collision(display, display->pdata->map, (int) (tmp_y / display->maps->map_s), (int)(tmp_x / display->maps->map_s)))
		{
			display->pos->x = tmp_x;
			display->pos->y = tmp_y;
		}
	}
	if (mlx_is_key_down(display->mlx, MLX_KEY_S))
	{
		tmp_x -= display->pos->dx;
		tmp_y -= display->pos->dy;
		if (!wall_collision(display, display->pdata->map, (int) (tmp_y / display->maps->map_s), (int)(tmp_x / display->maps->map_s)))
		{
			display->pos->x = tmp_x;
			display->pos->y = tmp_y;
		}
	}
		printf("DEBUG pos x is %d pos y is %d\n", (int)(tmp_x / display->maps->map_s), (int) (tmp_y / display->maps->map_s));
}

void	rotate(t_display *display)
{
	if (mlx_is_key_down(display->mlx, MLX_KEY_LEFT))
	{
		display->pos->a -= 0.05;
		display->pos->dx = cos(display->pos->a) * 5;
		display->pos->dy = sin(display->pos->a) * 5;
	}
	if (mlx_is_key_down(display->mlx, MLX_KEY_RIGHT))
	{
		display->pos->a += 0.05;
		display->pos->dx = cos(display->pos->a) * 5;
		display->pos->dy = sin(display->pos->a) * 5;
	}
	if (display->pos->a <= 0)
		display->pos->a += 2 * M_PI;
	if (display->pos->a >= 2 * M_PI)
		display->pos->a -= 2 * M_PI;
}

/*	keys W and S to move forward / backward, keys A and D to move sidewards */
/*	arrow keys to rotate */
void	my_hook(void *param)
{
	t_display	*display;

	display = param;
	(move_up_down(display));
	move_left_right(display);
	rotate(display);
	reset_angles(display);
	memset_window(display);
	printf("DEBUG\n");
	draw_floor_ceiling(display);
	draw_minimap(display);
	render(display, display->pos, display->ray, display->wall);
	return ;
}
