/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:05:10 by kczichow          #+#    #+#             */
/*   Updated: 2023/05/16 11:22:09 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/* allocate memory for all structs within t_display struct */
void allocate_memory(t_display *display)
{
	display->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
		if (!display->mlx)
			exit(EXIT_FAILURE);
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
		free (display->tex);
	if (display->mlx)
	{
		mlx_delete_image(display->mlx, display->mm_img);
		mlx_terminate(display->mlx);
	}
	if (display)
		free (display);
	// system ("leaks cub3D");
	return (0);
}