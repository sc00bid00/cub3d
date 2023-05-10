/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:05:30 by kczichow          #+#    #+#             */
/*   Updated: 2023/05/10 11:17:13 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <libft.h>
# include <unistd.h>
# include <MLX42.h>
# include <math.h>

#define mapS 64      //map cube size
#define WIDTH mapS * 8		// window width
#define HEIGHT mapS * 8	// window height
#define COLOR 0
#define DR 0.0174533 // 1 degree in radians
#define SCREEN_W 320 // screen width
#define SCREEN_H 160 // screen width


typedef struct s_wall
{
	int		count;
	float	dis_t; // distance to wall from player
	float	ca;
	float	line_h; // line height
	float	line_off; // full window height - line height / 2; line offset
	
}	t_wall;

// rays
typedef struct s_ray
{
	int		r;	// number of rays
	int		x;	// coordinate on grid
	int		y;	// coordinate on grid
	float	a;	// ray angle
	float	x0;	// coordinate in pixel
	float	y0; // coordinate in pixel
	float	x_off; // x offset in pixel
	float	y_off; // y offset in pixel
	float	hx;
	float 	hy;
	float	vx;
	float	vy;
	float	dis_h;
	float	dis_v;
	float	atan;
	float	ntan;
	
}	t_ray;
	
// player
typedef	struct s_pos
{
	float	x;	// coordinate on grid
	float	y;	// coordinate on grid
	float	dx; // delta x
	float	dy; // delta y
	float	a;	// player view angle
	float	x0; //	x coordinate of start position
	float	y0; // y coordinate of start position
	float	a0; // starting angle (derived from N, S, W, E)

}	t_pos;

// map


typedef struct s_maps
{
	int x;
	int y;
	int x0;		// coordinate in pixel value
	int y0;		// coordinate in pixel value
	int max_x;	// number of columns in map (x max);
	int max_y;  // number of rows in map (y max);
	// int map_s;
	int	x_coeff; // adjust map to pixel: WIDTH / map_x
	int	y_coeff; // adjust map to pixel: HEIGHT / may_y
	char	*arr[]; // parsed from cub file
	// und alle weiteren overhead parameter aus dem cub file
}	t_maps;

// overall struct to hold pointers to all structs
typedef struct s_display
{
	mlx_t			*mlx;
	mlx_image_t		*g_img;
	t_pos			*pos;
	t_maps			*maps;
	t_ray			*ray;
	t_wall			*wall;
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
void		draw_line(t_display *display, float posx, float posy);
void		draw_line_bresenham(t_display *display, int x_start, int y_start, int x_end, int y_end, int color);
void		draw_cube(t_display *display, bool wall);
void		calc_rays(t_display *display, t_pos *pos, t_ray *ray, t_wall *wall);
float		dist(t_pos *pos, float bx, float by, float ang);
void		draw_scene3D(t_display *display);

#endif
