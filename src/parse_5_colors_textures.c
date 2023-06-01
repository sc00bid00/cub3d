/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_5_colors_textures.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:29:58 by lsordo            #+#    #+#             */
/*   Updated: 2023/06/01 17:48:34 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	get_colors(t_pdata *p)
{
	t_list	*tmp;
	char	*dum;

	tmp = p->file_data;
	p->color_string = ft_calloc(3, sizeof(char *));
	if (!p->color_string)
		return (put_err(ERR_MEMORY));
	while (tmp)
	{
		dum = ft_strtrim(tmp->content, " \t");
		if (!ft_strncmp(dum, "F", 1))
			p->color_string[F] = ft_strtrim(dum, "F \t\n");
		else if (!ft_strncmp(dum, "C", 1))
			p->color_string[C] = ft_strtrim(dum, "C \t\n");
		free(dum);
		tmp = tmp->next;
	}
	if (!chk_colors(p))
		return (false);
	return ( true);
}

bool	chk_colors(t_pdata *p)
{
	int		i[2];
	int		colors[3];
	char	**arr;
	int		n;

	if (!chk_records(p))
		return (put_err(ERR_MISSINGCOLORS));
	i[0] = 0;
	while (p->color_string && p->color_string[i[0]])
	{
		arr = ft_split(p->color_string[i[0]], ',');
		i[1] = 0;
		while (arr && arr[i[1]])
		{
			n = ft_atoi(arr[i[1]]);
			if (n < 0 || n > 255)
				return (ft_freesplit(arr), put_err(ERR_COLORBYTE));
			else
				colors[i[1]++] = n;
		}
		if (i[1] != 3)
			return (ft_freesplit(arr), put_err(ERR_MISSINGCOLORS));
		p->colors_fc[i[0]] = get_rgba(colors[0], colors[1], colors[2]);
		ft_freesplit(arr);
		i[0]++;
	}
	return (true);
}

bool	get_textures(t_pdata *p)
{
	t_list	*tmp;
	char	*dum;

	tmp = p->file_data;
	p->textures_path = ft_calloc(5, sizeof(char *));
	if (!p->textures_path)
		return (put_err(ERR_MEMORY));
	while (tmp)
	{
		dum = ft_strtrim(tmp->content, " \t");
		if (!ft_strncmp(dum, "NO", 2))
			p->textures_path[NO] = ft_strtrim(dum, "NO \t\n");
		else if (!ft_strncmp(dum, "SO", 2))
			p->textures_path[SO] = ft_strtrim(dum, "SO \t\n");
		else if (!ft_strncmp(dum, "EA", 2))
			p->textures_path[EA] = ft_strtrim(dum, "EA \t\n");
		else if (!ft_strncmp(dum, "WE", 2))
			p->textures_path[WE] = ft_strtrim(dum, "WE \t\n");
		free(dum);
		tmp = tmp->next;
	}
	return (chk_textures(p));
}

bool	chk_textures(t_pdata *p)
{
	int	i;

	i = 0;
	while (p->textures_path[i])
		i++;
	if (i != 4)
		return(put_err(ERR_TEXTURENUMBER));
	i = 0;
	while (p->textures_path[i])
	{
		if (!mlx_load_png(p->textures_path[i]))
			return (false);
		else if (mlx_load_xpm42(p->textures_path[i]) && mlx_errno)
			return (false);
		i++;
	}
	return (true);
}

bool	chk_records(t_pdata *p)
{
	int	i;

	i = 0;
	while (p && p->color_string && p->color_string[i])
		i++;
	if (i != 2)
		return (false);

	return (true);
}
