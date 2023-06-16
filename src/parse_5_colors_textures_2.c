/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_5_colors_textures_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:37:10 by lsordo            #+#    #+#             */
/*   Updated: 2023/06/16 10:48:04 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	get_arrsize(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

int	chk_colorsdata(t_pdata *p)
{
	int		i[2];
	int		colors[3];
	char	**arr;
	int		n;

	i[0] = 0;
	while (p->color_string && p->color_string[i[0]])
	{
		arr = ft_split(p->color_string[i[0]], ',');
		if (get_arrsize(arr) != 3)
			return (ft_freesplit(arr), put_err(ERR_INPUT));
		i[1] = 0;
		while (arr && arr[i[1]])
		{
			n = ft_atoi(arr[i[1]]);
			if (n < 0 || n > 255)
				return (ft_freesplit(arr), put_err(ERR_COLORBYTE));
			else
				colors[i[1]++] = n;
		}
		p->colors_fc[i[0]] = get_rgba(colors[0], colors[1], colors[2]);
		ft_freesplit(arr);
		i[0]++;
	}
	return (0);
}
