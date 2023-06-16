/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_5_colors_textures.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:29:58 by lsordo            #+#    #+#             */
/*   Updated: 2023/06/16 15:51:16 by lsordo           ###   ########.fr       */
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
	return (true);
}

bool	chk_colors(t_pdata *p)
{
	int	i;
	int	j;
	int	commas;

	i = 0;
	while (p->color_string && p->color_string[i])
	{
		j = 0;
		commas = 0;
		while (p->color_string[i][j])
		{
			if (p->color_string[i][j++] == ',')
				commas++;
		}
		if (commas != 2)
			return (put_err(ERR_INPUT));
		i++;
	}
	if (!chk_records(p))
		return (put_err(ERR_MISSINGCOLORS));
	if (!chk_colorsdata(p))
		return (false);
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
	int				i;
	mlx_texture_t	*tmp;

	i = 0;
	while (p->textures_path[i])
		i++;
	if (i != 4)
		return (put_err(ERR_TEXTURENUMBER));
	i = 0;
	while (p->textures_path[i])
	{
		tmp = mlx_load_png(p->textures_path[i]);
		if (!tmp)
			return (false);
		i++;
		mlx_delete_texture(tmp);
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
