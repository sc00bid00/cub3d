/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:13:27 by kczichow          #+#    #+#             */
/*   Updated: 2023/05/22 18:38:36 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/* reset window to  */
void	memset_window(t_display *display)
{
	ft_memset(display->f_c_img->pixels, COLOR, WIDTH \
			* HEIGHT * sizeof(int32_t));
	ft_memset(display->s_img->pixels, COLOR, WIDTH \
			* HEIGHT * sizeof(int32_t));
	ft_memset(display->mm_img->pixels, COLOR, display->mm_img->width \
			* display->mm_img->height * sizeof(int32_t));
}

/* init window layers for floor/ceiling, scene and minimap */
void	setup_windows(t_display *display)
{
	display->f_c_img = mlx_new_image(display->mlx, WIDTH, HEIGHT);
	display->s_img = mlx_new_image(display->mlx, WIDTH, HEIGHT);
	display->mm_img = mlx_new_image(display->mlx, display->maps->width_mm, \
		display->maps->height_mm);
	memset_window(display);
}

/* put all image layers to window */
void	image_to_window(t_display *display)
{
	mlx_image_to_window(display->mlx, display->f_c_img, 0, 0);
	mlx_image_to_window(display->mlx, display->s_img, 0, 0);
	mlx_image_to_window(display->mlx, display->mm_img, 0, 0);
}
