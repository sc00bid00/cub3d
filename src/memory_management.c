/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:05:10 by kczichow          #+#    #+#             */
/*   Updated: 2023/06/12 18:08:31 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/* allocate memory for all structs within t_display struct */
void allocate_memory(t_display *display)
{
	display->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	if (!display->mlx)
	{
		clean_up(display);
		exit(EXIT_FAILURE);
	}
	display->pos = ft_calloc(1, sizeof(t_pos));
	if (!display->pos)
		clean_up(display);
	display->maps = ft_calloc(1, sizeof(t_maps));
	if (!display->maps)
		clean_up(display);
	display->ray = ft_calloc(1, sizeof(t_ray));
	if (!display->ray)
		clean_up(display);
	display->wall = ft_calloc(1, sizeof(t_wall));
	if (!display->wall)
		clean_up(display);
	display->tex = ft_calloc(5, sizeof(mlx_texture_t *));
	if (!display->tex)
		clean_up(display);
}
/* free texture datas */
void	free_textures(t_display *display)
{
	int	i;

	i = 0;
	while (i < 4)
		mlx_delete_texture(display->tex[i++]);
}
/*	free all allocated memory */
int	clean_up(t_display *display)
{
	tmp_freedisplay(display);
	if (display->pos)
		free (display->pos);
	if (display->maps)
		free (display->maps);
	if (display->ray)
		free (display->ray);
	if (display->wall)
		free (display->wall);
	if (display->tex)
	{
		free_textures(display);
		free(display->tex);
	}
	if (display->mlx)
	{
		// mlx_delete_image(display->mlx, display->mm_img);
		// mlx_delete_image(display->mlx, display->f_c_img);
		// mlx_delete_image(display->mlx, display->s_img);
		mlx_terminate(display->mlx);
	}
	if (display)
		free (display);
	// system ("leaks cub3D");
	return (0);
}
