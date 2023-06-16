/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:49:02 by lsordo            #+#    #+#             */
/*   Updated: 2023/06/16 09:40:06 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <debug.h>
#include <cub3d.h>

void	ft_freesplit_2(char **arr, int n)
{
	int	i;

	i = 0;
	while (arr && i < n)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

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

void	tmp_freelst(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (lst)
	{
		if (lst->content)
			free(lst->content);
		tmp = lst->next;
		free(lst);
		if (!tmp)
			break ;
		lst = tmp;
	}
}

void	tmp_freearr(char **arr)
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

void	tmp_freedisplay(t_display *d)
{
	if (d && d->pdata && d->pdata->file_data)
		tmp_freelst(d->pdata->file_data);
	if (d && d->pdata && d->pdata->textures_path)
		ft_freesplit_2(d->pdata->textures_path, 5);
	if (d && d->pdata && d->pdata->color_string)
		ft_freesplit_2(d->pdata->color_string, 3);
	if (d && d->pdata && d->pdata->map)
		ft_freesplit(d->pdata->map);
	if (d && d->pdata && d->pdata->map_testfill)
		ft_freesplit(d->pdata->map_testfill);
	if (d && d->pdata)
		free(d->pdata);
}
