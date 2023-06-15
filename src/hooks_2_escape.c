/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_2_escape.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:01:15 by kczichow          #+#    #+#             */
/*   Updated: 2023/06/15 17:53:11 by lsordo           ###   ########.fr       */
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

int	collision(t_display *d, double y, double x)
{
	if (d->pdata->map[(int)y][(int)x] == 49)
		return (1);
	return (0);
}
