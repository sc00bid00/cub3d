/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:49:02 by lsordo            #+#    #+#             */
/*   Updated: 2023/06/12 17:45:55 by lsordo           ###   ########.fr       */
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

void	tmp_prtlst(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	printf("=== debug tmp_prtlst ===\n");
	while (tmp)
	{
		printf("%s", (char *)tmp->content);
		tmp = tmp->next;
	}
	printf("=== debug tmp_prtlst ===\n");
}

void	tmp_freelst(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	printf("=== debug tmp_freelst ===\n");
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

void	tmp_prtarr(char **arr)
{
	int	i;

	printf("=== debug tmp_prtarr ===\n");
	i = 0;
	while (arr && arr[i])
	{
		printf("%s", arr[i]);
		i++;
	}
	printf("\n");
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
