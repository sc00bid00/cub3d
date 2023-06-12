/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:05:30 by kczichow          #+#    #+#             */
/*   Updated: 2023/06/12 14:09:34 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libft.h>
# include <debug.h>
# include <stdio.h>
# include <unistd.h>
# include <MLX42.h>
# include <math.h>
# include <fcntl.h>
# include <errors.h>
# include <stdbool.h>

#define WIDTH 1920
#define HEIGHT 1200	// players height 600 pixel
#define mapS 64   //map cube size
#define COLOR 0
#define DR 0.0174533 // 1 degree in radians
#define	COEFF 5


// variables related to 3D
typedef struct s_wall
{
	int				dir; // indicates if vertical or horizontal wall is hit by ray
	int				new_wall;
	double			dis_t; // distance to wall from player
	double			line_h; // line height
	double			line_w; // line width
	double			line_off; // (full window height - line height) / 2; line offset
	double			x0;	// pixel coordinate x
	double 			y0; // pixel coordinate y
	double			pos_x;
	double			pos_y;
	double			offset_x;
	mlx_texture_t	*texture;
	mlx_texture_t	*old_tex;

}	t_wall;

// rays
typedef struct s_ray
{
	int		r;	// number of rays
	int		ray_max;	// number of rays
	int		x;	// coordinate on grid
	int		y;	// coordinate on grid
	double	a;	// ray angle
	double	x0;	// coordinate in pixel
	double	y0; // coordinate in pixel
	double	x_off; // x offset in pixel
	double	y_off; // y offset in pixel
	double	hx;
	double 	hy;
	double	vx;
	double	vy;
	double	dis_h;
	double	dis_v;
	double	dis_t;
	double	atan;
	double	ntan;

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
	double		player_directionrad;
}	t_pdata;

// player
typedef	struct s_pos
{
	double	x;	// coordinate on grid
	double	y;	// coordinate on grid
	double	dx; // delta x
	double	dy; // delta y
	double	a;	// player view angle
	// double	x0; //	x coordinate of start position
	// double	y0; // y coordinate of start position
	double	fov;
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
	int		height_mm;
	int		width_mm;
	int		map_s;
}	t_maps;

// overall struct to hold pointers to all structs
typedef struct s_display
{
	mlx_t			*mlx;
	mlx_image_t		*s_img; // image layer for 3d scene
	mlx_image_t		*mm_img; // image layer for minimap
	mlx_image_t		*f_c_img; // image layer for floor and ceiling
	mlx_image_t		*img_tex; // test layer for texture
	mlx_texture_t	**tex; //texture
	t_pos			*pos;
	t_maps			*maps;
	t_pdata			*pdata;
	t_ray			*ray;
	t_ray			*ray_max;
	t_wall			*wall;
}	t_display;


// functions

/* MEMORY_MANAGEMENT */
void		allocate_memory(t_display *display);
int			clean_up(t_display *display);
/* SETUP	*/
void		setup_display(t_display *display);
void		setup_maps(t_maps *maps, t_pdata *pdata);
void		setup_pos(t_pos *pos, t_pdata *pdata, t_maps *maps);
void		setup_rays(t_ray *ray);
void		setup_wall(t_wall *wall, t_pos *pos);
/*	WINDOW	*/
void		memset_window(t_display *display);
void		setup_windows(t_display *display);
void		image_to_window(t_display *display);
/* MLX_UTILS */
void		load_tex(t_display *display, t_pdata *pdata);
/*	RAYS	*/
void		find_horizontal_intersec(t_display *display, t_pos *pos, t_ray *ray);
void		calc_next_h_intersection(t_display *display, t_pos *pos, t_ray *ray);
void		find_vertical_intersec(t_display *display, t_pos *pos, t_ray *ray);
void		calc_next_v_intersection(t_display *display, t_pos *pos, t_ray *ray);
void		compare_dist(t_ray *ray, t_wall *wall);
/* MINIMAP	*/
void		draw_minimap(t_display *display);
void		drawMap2D(t_display *display);
void		draw_player_mm(t_display *display);
void		draw_rays_2D(t_display *display, t_pos *pos, t_ray *ray);
/* DRAW		*/
void		draw_line(t_display *display, double posx, double posy);
void		draw_line_bresenham(t_display *display, int x_start, int y_start, int x_end, int y_end, int color);
void		draw_floor_ceiling(t_display *display);
void		my_put_pixel_mm(t_display *display, double x, double y, int color);
void		my_put_pixel(mlx_image_t *img, double x, double y, int color);
/*	HOOKS	*/
void		my_hook(void *param);
void		my_keyhook(mlx_key_data_t keydata, void *param);
void		move_left_right(t_display *display);
void		move_up_down(t_display	*display);
void		rotate(t_display *display);

uint32_t	get_rgba(uint8_t red, uint8_t green, uint8_t blue);
void		render(t_display *display, t_pos *pos, t_ray *ray, t_wall *wall);
double		dist(t_pos *pos, double bx, double by, double ang);
void		draw_scene3D(t_display *display);
void		draw_column(t_display *display, t_ray *ray, t_wall *wall, t_maps *maps);
void		calculate_3D_param(t_display *display, t_wall *wall, t_pos *pos, t_ray *ray);
void		reset_angles(t_display *display);
void		get_wall_dir(t_display *display);
int			img_pixel(double x_p, double y_p, mlx_texture_t *tex);
int			get_color(uint8_t *start);
// uint32_t	*get_color(mlx_texture_t *texture);

/* parse_1_init_check.c */
bool		chk_name(char *s);
bool		chk_args(int argc, char **argv);
bool		init_pdata(t_display *d, char **argv);
void		change_chartozero(t_pdata *p);
bool		put_err(error_t ERR_NUM);

/* parse_2_getdata.c */
bool		get_restofdata(t_pdata *p);
bool		get_data(t_pdata *p);
bool		get_rows(t_pdata *p);
bool		get_table(t_pdata *p);
bool		get_table_elements(t_pdata *p);

/* parse_3_table_fill.c */
void		flood_fill(int col, int row, t_pdata *p);
bool		chk_flood_fill(t_pdata *p);

/* parse_4_palyerdata.c */
bool		get_player(t_pdata *p);
bool		get_xypostion(int *player_chk, t_pdata *p, int i, int j);
void		get_direction(double *player_directionrad, char c);

/* parse_5_colors_textures.c */
bool		get_colors(t_pdata *p);
bool		chk_colors(t_pdata *p);
bool		get_textures(t_pdata *p);
bool		chk_textures(t_pdata *p);
bool		chk_records(t_pdata *p);

/* parse_6_other_check.c */
bool		chk_empty(char *str);
bool		chk_valid(t_list *tmp, int *chk);
bool		chk_data(t_pdata *p);
bool		chk_rows(t_pdata *p);

#endif
