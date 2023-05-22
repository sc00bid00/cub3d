/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:08:58 by kczichow          #+#    #+#             */
/*   Updated: 2023/05/22 10:39:07 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cub3d.h>

char	get_wall_tex(t_display *display)
{
	char	wall_tex;
	

	if (display->wall->hit == 0)
	{
		if (env->ray.stepx > 0 && env->ray.rmapx > \
		(int)env->ray.rposx && env->ray.wall == 0)
			wall_tex = 'W';
		if (env->ray.stepx < 0 && env->ray.rmapx < (int) \
		env->ray.rposx && env->ray.wall == 0)
			wall_tex = 'E';
	}
	if (env->ray.wall == 1)
	{
		if (env->ray.stepy > 0 && env->ray.rmapy > (int)env->ray.\
		rposy && env->ray.wall == 1)
			wall_tex = 'S';
		if (env->ray.stepy < 0 && env->ray.rmapy < (int)env->ray.\
		rposy && env->ray.wall - 0)
			wall_tex = 'N';
	}
	return (wall_tex);
}