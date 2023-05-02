/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:05:30 by kczichow          #+#    #+#             */
/*   Updated: 2023/05/02 16:56:58 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <libft.h>
#include <MLX42.h>

#define WIDTH 1025
#define HEIGHT 512

// position of the player

typedef	struct s_pos
{
	float	x;
	float	y;
	
}	t_pos;


// overall struct to hold pointers to all structs

typedef struct s_display
{
	mlx_t			*mlx;
	mlx_image_t		*g_img;
	t_pos			*pos;
}	t_display;


// functions

void	init_set(int argc, char **argv, t_display *display);
void	draw_player(t_display *display);
void	my_hook(void *param);

#endif