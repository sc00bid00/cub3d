/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:06:06 by lsordo            #+#    #+#             */
/*   Updated: 2023/05/11 18:51:13 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	put_err(error_t ERR_NUM)
{
	const char	*m[] = {NULL, \
		"cub3D: error: memory error\n", \
		"cub3D: error: wrong arguments number\n", \
		"cub3D: error: wrong filename\n", \
		"cub3D: error: file open failure\n", \
		"cub3D: error: input parameters not ok\n", \
		"cub3D: error: texture data\n", \
		"cub3d: error: wrong color ranges\n", \
		"cub3d: error: missinng color data\n", \
		"cub3D: error: missing map data\n", \
		"cub3D: error: maps contains ivalid data\n", \
		"cub3D: error: more players on the map\n", \
		"cub3D: error: invalid player position\n", \
		"cub3D: error: player missing\n", \
		"cub3D: error: invalid map design\n"};

	return (ft_putstr_fd((char *)m[ERR_NUM], 2), false);
}

bool	chk_empty(char *str)
{
	while (str && *str)
	{
		if (*str++ > 32)
			return (false);
	}
	return (true);
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
	while (p->textures_path[4])
	{
		if (!ft_strncmp(p->textures_path[i], ".png", ft_strlen(p->textures_path[i]) - 4) \
			&& mlx_load_png(p->textures_path[i]) && mlx_errno)
				return (false);
		else if (mlx_load_xpm42(p->textures_path[i]) && mlx_errno)
			return (false);
		i++;
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
			p->textures_path[NO] = ft_strtrim(dum, "NO \t");
		else if (!ft_strncmp(dum, "SO", 2))
			p->textures_path[SO] = ft_strtrim(dum, "SO \t");
		else if (!ft_strncmp(dum, "EA", 2))
			p->textures_path[EA] = ft_strtrim(dum, "EA \t");
		else if (!ft_strncmp(dum, "WE", 2))
			p->textures_path[WE] = ft_strtrim(dum, "WE \t");
		free(dum);
		tmp = tmp->next;
	}
	return (chk_textures(p) && true);
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

bool	chk_colors(t_pdata *p)
{
	int		i[2];
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
				p->colors_fc[i[0]] |= n << (unsigned)(24 - i[1]++ * 8);
		}
		if (i[1] != 3)
			return (ft_freesplit(arr), put_err(ERR_MISSINGCOLORS));
		ft_freesplit(arr);
		i[0]++;
	}
	return (true);
}

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
			p->color_string[F] = ft_strtrim(dum, "F \t");
		else if (!ft_strncmp(dum, "C", 1))
			p->color_string[C] = ft_strtrim(dum, "C \t");
		free(dum);
		tmp = tmp->next;
	}
	if (!chk_colors(p))
		return (false);
	return ( true);
}

bool	chk_valid(t_list *tmp, int *chk)
{
	char	*dum;
	int		flag;
	char	*test;

	test = "NSWEFC";
	while (tmp)
	{
		flag = 0b000000;
		if (tmp->content)
			dum = ft_strtrim(tmp->content, " \t");
		if (dum && !ft_strchr(test, dum[0]) && !ft_strchr("01", dum[0]))
			return (free(dum), false);
		else if (!ft_strchr("01", dum[0]))
		{
			flag |= 1 << (ft_strchr(test, dum[0]) - test);
			if (flag & *chk)
				return (free(dum), false);
			else
				*chk |= flag;
		}
		if (dum)
			free(dum);
		tmp = tmp->next;
	}
	return (true);
}

bool	chk_data(t_pdata *p)
{
	t_list	*tmp;
	int		chk;

	tmp = p->file_data;
	chk = 0b000000;
	if (!chk_valid(tmp, &chk) || chk != 0b111111)
		return (put_err(ERR_INPUT));
	return (true);
}
bool	chk_rows(t_pdata *p)
{
	int	i;
	int	j;

	i = 0;
	while (p->map[i])
	{
		j = 0;
		while (p->map[i][j])
		{
			if (!ft_strchr(" 01NSEW\n", p->map[i][j]))
				return (put_err(ERR_MAPDATA), false);
			j++;
		}
		i++;
	}
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
		ft_memcpy(p->map[i], tmp->content, (size_t)p->num_cols);
		ft_memcpy(p->map_testfill[i], tmp->content, (size_t)p->num_cols);
		i++;
		tmp = tmp->next;
	}
	change_chartozero(p);
	return (true);
}
void	get_direction(float *player_directionrad, char c)
{
	if (c == 'E')
		*player_directionrad = 0;
	else if (c == 'N')
		*player_directionrad = M_PI_2;
	else if (c == 'W')
		*player_directionrad = M_PI;
	else if (c == 'S')
		*player_directionrad = 1.5 * M_PI;
}

bool	get_xypostion(int *player_chk, t_pdata *p, int i, int j)
{
	if(!*player_chk && ft_strchr("NSEW", p->map[i][j]))
	{
		*player_chk = 1;
		p->player_positionxy[0] = j;
		p->player_positionxy[1] = i;
		if (p->player_positionxy[0] == 0 \
			|| p->player_positionxy[0] == p->num_cols - 2 \
			|| p->player_positionxy[1] == 0 \
			|| p->player_positionxy[1] == p->num_rows - 1)
				return(put_err(ERR_PLAYERPOSITION), false);
		get_direction(&p->player_directionrad, p->map[i][j]);
	}
	else if (ft_strchr("NSEW", p->map[i][j]) && player_chk)
		return (put_err(ERR_MOREPLAYERS), false);
	return (true);
}

bool	get_player(t_pdata *p)
{
	int	i;
	int	j;
	int	player_chk;

	player_chk = 0;
	i = 0;
	while (p->map[i])
	{
		j = 0;
		while (p->map[i][j])
		{
			if (!get_xypostion(&player_chk, p, i, j))
				return (false);
			j++;
		}
		i++;
	}
	if (!player_chk)
		return (put_err(ERR_MISSINGPLAYER), false);
	return (true);
}

void	flood_fill(int col, int row, t_pdata *p)
{
	if (col < 0 || col > p->num_cols - 1 || row < 0 || row > p->num_rows - 1)
		return ;
	if (!ft_strchr("0NSEW", p->map_testfill[row][col]))
		return ;
	p->map_testfill[row][col] = 'x';
	flood_fill(col, row - 1, p);
	flood_fill(col, row + 1, p);
	flood_fill(col - 1, row, p);
	flood_fill(col + 1, row, p);
	return ;
}
bool	chk_flood_fill(t_pdata *p)
{
	int	i;

	if (ft_strchr(p->map_testfill[0], 'x')
		|| ft_strchr(p->map_testfill[p->num_rows - 1], 'x'))
			return (false);
	i = 0;
	while (i < p->num_rows)
	{
		if (p->map_testfill[i][0] == 'x' \
			|| p->map_testfill[i][p->num_cols - 2] == 'x')
				return(false);
		i++;
	}
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

/* error management and testing purpose */
int	main(int argc, char **argv)
{
	t_display	*d;

	d = ft_calloc(1, sizeof(t_display));
	if (!d)
		return (put_err(ERR_MEMORY));
	if (chk_args(argc, argv))
	{
		if (init_pdata(d, argv) && get_data(d->pdata))
			/* if we are here all input data should be ok */
			;
	}
	tmp_freedisplay(d);
	return (0);
}
