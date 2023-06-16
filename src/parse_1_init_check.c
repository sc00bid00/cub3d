/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_1_init_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:42:38 by lsordo            #+#    #+#             */
/*   Updated: 2023/06/16 11:29:40 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	chk_name(char *s)
{
	char	*str;

	if (s && ft_strlen(s) > 4)
	{
		str = s + ft_strlen(s) - 4;
		if (!ft_strncmp(str, ".cub", 4))
			return (true);
	}
	return (false);
}

bool	chk_args(int argc, char **argv)
{
	if (argc != 2)
		return (put_err(ERR_ARGNUMBER));
	if (!chk_name(argv[1]))
		return (put_err(ERR_FILENAME));
	return (true);
}

bool	init_pdata(t_display *d, char **argv)
{
	d->pdata = ft_calloc(1, sizeof(t_pdata));
	if (!d->pdata)
		return (put_err(ERR_MEMORY));
	ft_bzero(d->pdata, sizeof(t_pdata));
	d->pdata->argv = argv;
	return (true);
}

void	change_chartozero(t_pdata *p)
{
	int	i;
	int	j;

	i = 0;
	while (i < p->num_rows)
	{
		j = 0;
		while (j < p->num_cols - 1)
		{
			if (ft_strchr(" \n", p->map[i][j]))
			{
				p->map[i][j] = '0';
				p->map_testfill[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

bool	put_err(t_error ERR_NUM)
{
	const char	*m[] = {NULL, \
		"cub3D: error: memory error\n", \
		"cub3D: error: wrong arguments number\n", \
		"cub3D: error: wrong filename\n", \
		"cub3D: error: file open failure\n", \
		"cub3D: error: input parameters not ok\n", \
		"cub3D: error: texture data\n", \
		"cub3d: error: wrong color input\n", \
		"cub3d: error: missing color data\n", \
		"cub3D: error: missing map data\n", \
		"cub3D: error: maps contains ivalid data\n", \
		"cub3D: error: more players on the map\n", \
		"cub3D: error: invalid player position\n", \
		"cub3D: error: player missing\n", \
		"cub3D: error: invalid map design\n"};

	return (ft_putstr_fd((char *)m[ERR_NUM], 2), false);
}
