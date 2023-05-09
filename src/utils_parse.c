/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:06:06 by lsordo            #+#    #+#             */
/*   Updated: 2023/05/09 10:58:24 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	put_msg(int num)
{
	if (num == ERR)
		ft_putstr_fd("cub3D: error\n", 2);
	if (num == ERR_NARG)
		ft_putstr_fd("cub3D: error: wrong arguments number\n", 2);
	if (num == ERR_NAME)
		ft_putstr_fd("cub3D: error: wrong filename\n", 2);
	if (num == ERR_NTEX)
		ft_putstr_fd("cub3D: error: missing texture data\n", 2);
	if (num == ERR_PTEX)
		ft_putstr_fd("cub3D: error: wrong texture path\n", 2);
	if (num == ERR_MTEX)
		ft_putstr_fd("cub3D: error: equivocal texture data\n", 2);
	if (num == ERR_COLS)
		ft_putstr_fd("cub3D: error: floor-ceiling colors overflow\n", 2);
	if (num == ERR_FLCL)
		ft_putstr_fd("cub3D: error: wrong number of floor-ceiling parameters\n", 2);
	if (num == ERR_NTBL)
		ft_putstr_fd("cub3D: error: no table found\n", 2);
	if (num == ERR_NALL)
		ft_putstr_fd("cub3D: error: data not allowed\n", 2);

	return (false);
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

bool	chk_permit(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	else
		close(fd);
	return (true);
}

bool	chk_textures(t_pdata *p)
{
	int	i;

	i = 0;
	while (p->tex[i])
		i++;
	if (i != 4)
		return(put_msg(ERR_NTEX));
	i = 0;
	while (p->tex[i])
	{
		if (!chk_permit(p->tex[i]))
			return (put_msg(ERR_PTEX));
		if (!mlx_load_png(p->tex[i]) && !mlx_load_xpm42(p->tex[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	get_textures(t_pdata *p)
{
	t_list	*tmp;
	char	*dum;

	tmp = p->fdata;
	p->tex = ft_calloc(5, sizeof(char *));
	while (tmp)
	{
		dum = ft_strtrim(tmp->content, " ");
		if (!ft_strncmp(dum, "NO", 2))
			p->tex[NO] = ft_strtrim(dum, "NO ");
		else if (!ft_strncmp(dum, "SO", 2))
			p->tex[SO] = ft_strtrim(dum, "SO ");
		else if (!ft_strncmp(dum, "EA", 2))
			p->tex[EA] = ft_strtrim(dum, "EA ");
		else if (!ft_strncmp(dum, "WE", 2))
			p->tex[WE] = ft_strtrim(dum, "WE ");
		free(dum);
		tmp = tmp->next;
	}
	return (chk_textures(p) && true);
}
bool	chk_rec(t_pdata *p)
{
	int	i;

	i = 0;
	while (p && p->info && p->info[i])
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

	if (!chk_rec(p))
		return (put_msg(ERR_FLCL));
	i[0] = 0;
	while (p->info && p->info[i[0]])
	{
		arr = ft_split(p->info[i[0]], ',');
		i[1] = 0;
		while (arr && arr[i[1]])
		{
			n = ft_atoi(arr[i[1]]);
			if (n < 0 || n > 255)
				return (ft_freesplit(arr), put_msg(ERR_COLS));
			else
				p->fc[i[0]] |= n << (unsigned)(24 - i[1]++ * 8);
		}
		if (i[1] != 3)
			return (ft_freesplit(arr), put_msg(ERR_FLCL));
		ft_freesplit(arr);
		i[0]++;
	}
	return (true);
}

bool	get_colors(t_pdata *p)
{
	t_list	*tmp;
	char	*dum;

	tmp = p->fdata;
	p->info = ft_calloc(3, sizeof(char *));
	while (tmp)
	{
		dum = ft_strtrim(tmp->content, " ");
		if (!ft_strncmp(dum, "F", 1))
			p->info[F] = ft_strtrim(dum, "F ");
		else if (!ft_strncmp(dum, "C", 1))
			p->info[C] = ft_strtrim(dum, "C ");
		else if ((dum[0] == 'F') \
			|| ((dum[0] == 'C')))
			return(free(dum), put_msg(ERR_FLCL));
		free(dum);
		tmp = tmp->next;
	}
	tmp_prtlst(p->fdata);
	tmp_prtarr(p->info);
	p->fc[0] = 0;
	p->fc[1] = 0;
	if (!chk_colors(p))
		return (false);
	return (true);
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
			dum = ft_strtrim(tmp->content, " ");
		if (dum && !ft_strchr(test, dum[0]) && dum[0] != '1')
			return (free(dum), false);
		else if (dum[0] != '1')
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

	tmp = p->fdata;
	chk = 0b000000;
	if (!chk_valid(tmp, &chk) || chk != 0b111111)
		return (put_msg(ERR_NALL));
	return (true);
}

bool	get_everything(t_pdata *p)
{
	if (!chk_data(p))
		return (false);
	if	(!get_textures(p))
		return (false);
	if (!get_colors(p))
		return (false);
	// if (!ft_gettable(p))
	// 	return (false);
	return (true);
}

bool	get_data(t_pdata *p)
{
	int		fd;
	char	*buf;

	p->fdata = NULL;
	fd = open(p->argv[1], O_RDONLY);
	if (fd < 0)
		return (put_msg(ERR_OPEN));
	while (1)
	{
		buf = get_next_line(fd);
		if (!buf)
			break ;
		if (!chk_empty(buf))
			ft_lstadd_back(&(p->fdata), ft_lstnew(ft_strdup(buf)));
		free(buf);
	}
	close (fd);
	return (get_everything(p) && true);
}

bool	ft_checkname(char *s)
{
	char	*str;

	if (s && ft_strlen(s) > 4)
	{
		str = s + ft_strlen(s) - 4;
		if (ft_strncmp(str, ".cub", 4))
			return (true);
	}
	else
		return (true);
	return (false);
}

bool	chk_args(int argc, char **argv)
{
	if (argc != 2)
		return (put_msg(ERR_NARG));
	if (ft_checkname(argv[1]))
		return (put_msg(ERR_NAME));
	return (true);
}

/* error management and testing purpose */
int	main(int argc, char **argv)
{
	t_display	*d;

	d = ft_calloc(1, sizeof(t_display));
	if (chk_args(argc, argv))
	{
		d->pdata = ft_calloc(1, sizeof(t_pdata));
		d->pdata->argv = argv;
		d->pdata->fdata = NULL;
		if (get_data(d->pdata))
			/* if we are here all input data should be ok */
			;
	}
	tmp_freedisplay(d);
	return (0);
}
