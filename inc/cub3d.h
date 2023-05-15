/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:05:30 by kczichow          #+#    #+#             */
/*   Updated: 2023/05/15 13:13:29 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libft.h>
# include <stdio.h>
# include <debug.h>
# include <unistd.h>
# include <MLX42.h>
# include <math.h>
# include <fcntl.h>
# include <errors.h>

#define WIDTH 1920	
#define HEIGHT 1200	// players height 600 pixel
#define WIDTH_MM 400
#define	HEIGHT_MM 400
#define mapS 50   //map cube size
#define COLOR 0
#define DR 0.0174533 // 1 degree in radians


// variables related to 3D
typedef struct s_wall
{
	int			count;
	float		dis_t; // distance to wall from player
	float		ca; // angle between player and ray
	float		line_h; // line height
	float		line_off; // (full window height - line height) / 2; line offset
	float		x0;	// pixel coordinate x
	float 		y0; // pixel coordinate y
	float		pos_x;
	float		pos_y;
	uint32_t	shading;
	
}	t_wall;

// rays
typedef struct s_ray
{
	int		r;	// number of rays
	int		ray_max;	// number of rays
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
	float	dis_t;
	float	atan;
	float	ntan;
	
}	t_ray;
	
enum	texture_index
{
	NO,
	SO,
	EA,
	WE
};

enum	colors_index
{
	F,
	C
};

/* t_pdata = structure to collect all parsed data
fdata		support list with all lines from gnl
			(support = needed for parsing purposes only)
first		support pointer to the first table line
tab			table array
max_len		longest line in the table (num of columns = width)
num_lines	number of lines (height)
tex			textures array indexed by tex_ix
info		support array for floor and ceiling colors indexed by fc_ix
fd			[0] floor [1] ceiling colors, both unsigned
play_tab	starting player position in tabe coodinates (x,y)
play_dir	starting player orientation in radiants
*/
typedef struct s_pdata
{
	char		**argv;
	t_list		*file_data;
	t_list		*first_maprow;
	char		**map;
	char		**map_testfill;
	int			num_cols;
	int			num_rows;
	char		**textures_path;
	char		**color_string;
	uint32_t	colors_fc[2];
	int			player_positionxy[2];
	float		player_directionrad;
}	t_pdata;

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
	float	x0_s;	// coordinate on 3d scale
	float	y0_s;	// coordinate on 3d scale
}	t_pos;

// map
typedef struct s_maps
{

	int		x;
	int		y;
	int		x0;		// coordinate in pixel value
	int		y0;		// coordinate in pixel value
	int		max_x;	// number of columns in map (x max) (from cub file?)
	int		max_y;  // number of rows in map (y max) (from cub file?)
	// int map_s;
	int		x_coeff; // adjust map to pixel: WIDTH / map_x
	int		y_coeff; // adjust map to pixel: HEIGHT / may_y
	char	**par;// all other overhead parameter from cub file, exact format tbd
}	t_maps;

// overall struct to hold pointers to all structs
typedef struct s_display
{
	mlx_t			*mlx;
	mlx_image_t		*s_img; // image layer for 3d scene
	mlx_image_t		*mm_img; // image layer for minimap
	mlx_image_t		*f_c_img; // image layer for floor and ceiling
	t_pos			*pos;
	t_maps			*maps;
	t_pdata			*pdata;
	t_ray			*ray;
	t_ray			*ray_max;
	t_wall			*wall;
}	t_display;


// functions
void		init_display(int argc, char **argv, t_display *display);
void		draw_minimap(t_display *display);
void		draw_player_mm(t_display *display);
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
void		draw_column(t_display *display, t_ray *ray, t_wall *wall, t_maps *maps);
void		calculate_3D_param(t_wall *wall, t_pos *pos, t_ray *ray);
#endif
