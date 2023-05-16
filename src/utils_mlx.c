/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 10:57:28 by kczichow          #+#    #+#             */
/*   Updated: 2023/05/16 11:03:56 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cub3d.h>

/* setup all three window layers */
void	memset_window(t_display *display)
{
	ft_memset(display->f_c_img->pixels, 100, display->f_c_img->width \
			* display->f_c_img->height * sizeof(int32_t));
	ft_memset(display->s_img->pixels, COLOR, display->s_img->width \
			* display->s_img->height * sizeof(int32_t));
	ft_memset(display->mm_img->pixels, COLOR, display->mm_img->width \
			* display->mm_img->height * sizeof(int32_t));
}
