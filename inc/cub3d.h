/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:05:30 by kczichow          #+#    #+#             */
/*   Updated: 2023/05/03 16:04:36 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <libft.h>
# include <unistd.h>
# include <MLX42.h>
# include <math.h>

#define WIDTH 1024		// window width
#define HEIGHT 1024		// window height
#define mapX  8			//  width
#define mapY  8			// map height
#define mapS 64      //map cube size
#define COLOR 0
#define PI 3.14159265359

// position of the player

typedef	struct s_pos
{
	float	x;
	float	y;
	float	dx; //	delta x
	float	dy; //	delta y
	float	a;	//	angle
	
}	t_pos;

typedef struct s_maps
{
	int x;
	int y;
	int xo;		// coordinate in pixel value
	int yo;		// coordinate in pixel value
	int map_x;	// number of columns in map (x max);
	int map_y;  // number of rows in map (y max);
	// int map_s;
	int	x_coeff; // adjust map to pixel: WIDTH / map_x
	int	y_coeff; // adjust map to pixel: HEIGHT / may_y
}	t_maps;

// overall struct to hold pointers to all structs
typedef struct s_display
{
	mlx_t			*mlx;
	mlx_image_t		*g_img;
	t_pos			*pos;
	t_maps			*maps;
}	t_display;


// functions
void		init_display(int argc, char **argv, t_display *display);
void		draw_player(t_display *display);
void		my_hook(void *param);
void		my_keyhook(mlx_key_data_t keydata, void *param);
int			clean_up(t_display *display);
void		allocate_memory(t_display *display);
uint32_t	get_rgba(uint8_t red, uint8_t green, uint8_t blue);
void		my_put_pixel(t_display *display);
void		drawMap2D(t_display *display);
void		draw_line(t_display *display);
void		draw_line_bresenham(t_display *display, int x_start, int y_start, int x_end, int y_end);

#endif