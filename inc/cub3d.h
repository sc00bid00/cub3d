/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:05:30 by kczichow          #+#    #+#             */
/*   Updated: 2023/06/16 09:39:08 by lsordo           ###   ########.fr       */
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

/*
players height at 600 pixel
mapS = map cube size
DR = degrees in radians
*/

# define WIDTH 1920
# define HEIGHT 1280
# define MAPS 64
# define COLOR 0
# define DR 0.0174533
# define COEFF 5

/* t_wall = struct to hold all variables need for 3D projection
dir			ndicates if vertical or horizontal wall is hit by ray
line_h		line height
line_w		distance to projection plane
line_off	(HEIGHT - line height) / 2: line offset
x0			pixel coordinate x
y0			pixel coordinate y
*/
typedef struct s_wall
{
	int				dir;
	double			dis_t;
	double			line_h;
	double			line_w;
	double			line_off;
	double			x0;
	double			y0;
	double			pos_x;
	double			pos_y;
	double			offset_x;
	mlx_texture_t	*texture;
	mlx_texture_t	*old_tex;

}	t_wall;

/*	t_ray = struct to hold all information related to rays
r			number of rays
ray_max 	max number of rays
x			coordinate on grid
y			coordinate on grid
a			ray angle
x0			coordinate in pixel
y0			coordinate in pixel
x_off		x offset in pixel
y_off		y offset in pixel
*/
typedef struct s_ray
{
	int		r;
	int		ray_max;
	int		x;
	int		y;
	double	a;
	double	x0;
	double	y0;
	double	x_off;
	double	y_off;
	double	hx;
	double	hy;
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

typedef struct s_bresenham
{
	int		x_start;
	int		y_start;
	int		x_end;
	int		y_end;
	int		dist[2];
	int		s[2];
	int		e2;
	int		err;
}t_bresenham;


/*	t_pos = struct to hold player data
x		coordinate on grid
y		coordinate on grid
dx		delta x
dy		delta y
a		player view angle
fov		field of view, initialized to 60 degrees (in radians)
*/
typedef struct s_pos
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	a;
	double	fov;
}	t_pos;

/*	t_maps = struct to hold map information
x0		coordinate in pixel value
y0		coordinate in pixel value
max_x	number of columns in map
max_y	number of rows in map
map_s	number of pixel per cube in minimap
*/
typedef struct s_maps
{
	int		x;
	int		y;
	int		x0;
	int		y0;
	int		max_x;
	int		max_y;
	int		height_mm;
	int		width_mm;
	int		map_s;
}	t_maps;

/* t_display = overall struct to hold pointers to all structs
s_img		image layer for 3d scene
mm_img		image layer for minimap
f_c_img		image layer for floor and ceiling
*/
typedef struct s_display
{
	mlx_t			*mlx;
	mlx_image_t		*s_img;
	mlx_image_t		*mm_img;
	mlx_image_t		*f_c_img;
	// mlx_image_t		*img_tex; // test layer for texture
	mlx_texture_t	**tex;
	t_pos			*pos;
	t_maps			*maps;
	t_pdata			*pdata;
	t_ray			*ray;
	t_ray			*ray_max;
	t_wall			*wall;
	t_bresenham		*bresenham;
}	t_display;

/* FUNCTIONS */

/* MEMORY_MANAGEMENT */
void		allocate_memory(t_display *display);
void		free_textures(t_display *display);
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
/*	RAYS	*/
void		find_horizontal_intersec(t_display *display, t_pos *pos, t_ray *ray);
void		calc_next_h_intersection(t_display *display, t_pos *pos, t_ray *ray);
void		find_vertical_intersec(t_display *display, t_pos *pos, t_ray *ray);
void		calc_next_v_intersection(t_display *display, t_pos *pos, t_ray *ray);
void		compare_dist(t_ray *ray, t_wall *wall);
/* MINIMAP	*/
void		draw_minimap(t_display *display);
void		draw_rays(t_display *display, t_pos *pos, t_ray *ray);
/* DRAW		*/
void		draw_line(t_display *d, int color);
// void		bresenham(t_display *display, double x_start, double y_start, double x_end, double y_end);
void		bresenham(t_display *display, int color);
void		my_put_pixel_mm(t_display *display, double x, double y, int color);
void		my_put_pixel(mlx_image_t *img, double x, double y, int color);
void		draw_floor_ceiling(t_display *display);
/*	HOOKS_1_MOVEMENT */
int			border(t_display *d, double y, double x);
int			collision(t_display *d, double y, double x);
void		move_left_right(t_display *display);
void		move_up_down(t_display	*display);
void		rotate(t_display *display);
void		my_hook(void *param);
/*	HOOKS_2_ESCAPE	*/
void		my_keyhook(mlx_key_data_t keydata, void *param);
/*	SCENE	*/
void		calc_3d_param(t_display *d, t_wall *wall, t_pos *pos, t_ray *ray);
void		draw_column(t_display *display, t_ray *ray, t_wall *wall);
/*	RENDERING	*/
void		render(t_display *display, t_pos *pos, t_ray *ray, t_wall *wall);
/*	RESSET	*/
void		reset_offset(t_wall *wall);
void		reset_player_angle(t_pos *pos);
void		reset_ray_angle(t_display *display);
/*	TEXTURE	*/
void		get_wall_dir(t_display *display);
void		load_tex(t_display *display, t_pdata *pdata);
int			get_color(uint8_t *start);
int			img_pixel(double x_p, double y_p, mlx_texture_t *tex);
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
void		get_numcols(t_list *tmp, t_pdata *p);

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


uint32_t	get_rgba(uint8_t red, uint8_t green, uint8_t blue);
double		dist(t_pos *pos, double bx, double by, double ang);

#endif
