/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:06:06 by lsordo            #+#    #+#             */
/*   Updated: 2023/05/08 15:31:28 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	ft_freesplit(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

bool	m_error(int num)
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
	if (num == ERR_FLCL)
		ft_putstr_fd("cub3D: error: wrong floor/ ceiling data\n", 2);
	return (false);
}

bool	emptyline(char *str)
{
	while (str && *str)
	{
		if (*str++ > 32)
			return (false);
	}
	return (true);
}

bool	file_permission(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	else
		close(fd);
	return (true);
}

bool	checktextures(t_pdata *p)
{
	int	i;

	i = 0;
	while (p->tex[i])
		i++;
	if (i != 4)
		return(m_error(ERR_NTEX));
	i = 0;
	while (p->tex[i])
	{
		if (!file_permission(p->tex[i]))
			return (m_error(ERR_PTEX));
		if (!mlx_load_png(p->tex[i]) && !mlx_load_xpm42(p->tex[i]))
			return (false);
		i++;
	}
	return (true);
}


bool	ft_gettextures(t_pdata *p)
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
	if (!checktextures(p))
		return (false);
	return (true);
}
bool	ft_checkfc(t_pdata *p, char **info)
{
	int		i[2];
	char	**arr;
	int		n;

	i[0] = 0;
	while (info && info[i[0]])
	{
		arr = ft_split(info[i[0]], ',');
		i[1] = 0;
		while (arr && arr[i[1]])
		{
			n = ft_atoi(arr[i[1]]);
			if (n < 0 || n > 255 || i[0] > 2 || i[1] > 3)
			{
				ft_freesplit(arr);
				return (m_error(ERR_FLCL));
			}
			else
				p->fc[i[0]] |= n << (unsigned)(24 - i[1] * 8);
			i[1]++;
		}
		ft_freesplit(arr);
		i[0]++;
	}
	return (true);
}

bool	ft_getflcl(t_pdata *p)
{
	t_list	*tmp;
	char	*dum;
	char	**info;

	tmp = p->fdata;
	info = ft_calloc(3, sizeof(char *));
	while (tmp)
	{
		dum = ft_strtrim(tmp->content, " ");
		if (!ft_strncmp(dum, "F", 1))
			info[F] = ft_strtrim(dum, "F ");
		else if (!ft_strncmp(dum, "C", 1))
			info[C] = ft_strtrim(dum, "C ");
		free(dum);
		tmp = tmp->next;
	}
	p->fc[0] = 0;
	p->fc[1] = 0;
	if (!ft_checkfc(p, info))
		return (false);
	return (true);
}

bool	ft_getdata(t_pdata	*p)
{
	int		fd;
	char	*buf;

	p->fdata = NULL;
	fd = open(p->argv[1], O_RDONLY);
	if (fd < 0)
		return (m_error(ERR_OPEN));
	while (1)
	{
		buf = get_next_line(fd);
		if (!buf)
			break ;
		if (!emptyline(buf))
			ft_lstadd_back(&(p->fdata), ft_lstnew(ft_strdup(buf)));
		free(buf);
	}
	close (fd);
	// if(!ft_gettextures(p))
	// 	return (false);
	if (!ft_getflcl(p))
		return (false);
	// if (!ft_gettable(p))
	// 	return (false);
	return (true);
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

bool	argcheck(int argc, char **argv)
{
	if (argc != 2)
		return (m_error(ERR_NARG));
	if (ft_checkname(argv[1]))
		return (m_error(ERR_NAME));
	return (true);
}

/* error management and testing purpose */
int	main(int argc, char **argv)
{
	t_display	*d;

	d = ft_calloc(1, sizeof(t_display));
	if (argcheck(argc, argv))
	{
		d->pdata = ft_calloc(1, sizeof(t_pdata));
		d->pdata->argv = argv;
		d->pdata->fdata = NULL;
		if (ft_getdata(d->pdata))
			;
			/* if we are here all input data should be ok */
	}
	tmp_freedisplay(d);
	return (0);
}
