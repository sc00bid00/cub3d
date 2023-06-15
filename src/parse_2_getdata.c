/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2_getdata.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:45:25 by lsordo            #+#    #+#             */
/*   Updated: 2023/06/15 17:21:00 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	get_restofdata(t_pdata *p)
{
	if	(!get_textures(p))
		return (false);
	if (!get_colors(p))
		return (false);
	if (!get_table(p))
		return (false);
	return (true);
}
bool	get_data(t_pdata *p)
{
	int		fd;
	char	*buf;

	p->file_data = NULL;
	fd = open(p->argv[1], O_RDONLY);
	if (fd < 0)
		return (put_err(ERR_OPENFILE));
	while (1)
	{
		buf = get_next_line(fd);
		if (!buf)
			break ;
		if (!chk_empty(buf))
			ft_lstadd_back(&(p->file_data), ft_lstnew(ft_strdup(buf)));
		free(buf);
	}
	close (fd);
	if (!chk_data(p))
		return (false);
	return (get_restofdata(p));
}
bool	get_rows(t_pdata *p)
{
	t_list	*tmp;
	int		i;

	tmp = p->first_maprow;
	p->map = ft_calloc(p->num_rows + 1, sizeof(char *));
	p->map_testfill = ft_calloc(p->num_rows + 1, sizeof(char *));
	if (!p->map || !p->map_testfill)
		return (put_err(ERR_MEMORY));
	i = 0;
	while (tmp)
	{
		p->map[i] = ft_calloc(p->num_cols + 1, 1);
		p->map_testfill[i] = ft_calloc(p->num_cols + 1, 1);
		ft_memcpy(p->map[i], tmp->content, (size_t)ft_strlen((char *)(tmp->content)) - 1);
		ft_memcpy(p->map_testfill[i], tmp->content, (size_t)ft_strlen((char *)(tmp->content)) - 1);
		i++;
		tmp = tmp->next;
	}
	change_chartozero(p);
	return (true);
}
bool	get_table(t_pdata *p)
{
	t_list	*tmp;
	char	*dum;

	p->first_maprow = p->file_data;
	while (p->first_maprow)
	{
		dum = ft_strtrim(p->first_maprow->content, " \t");
		if (ft_strchr("01", dum[0]))
		{
			free(dum);
			break ;
		}
		free(dum);
		p->first_maprow = p->first_maprow->next;
	}
	if (!p->first_maprow)
		return(put_err(ERR_NOTABLE));
	tmp = p->first_maprow;
	while (tmp)
	{
		if (tmp->content && p->num_cols < (int)ft_strlen(tmp->content))
			p->num_cols = ft_strlen(tmp->content);
		p->num_rows++;
		tmp = tmp->next;
	}
	if (!get_table_elements(p))
		return (false);
	return (true);
}
bool	get_table_elements(t_pdata *p)
{
	if (!get_rows(p))
		return (false);
	if (!chk_rows(p))
		return (false);
	if (!get_player(p))
		return (false);
	flood_fill(p->player_positionxy[0], p->player_positionxy[1], p);
	if (!chk_flood_fill(p))
		return (put_err(ERR_MAPDESIGN), false);
	return (true);
}
