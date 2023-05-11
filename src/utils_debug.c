/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:49:02 by lsordo            #+#    #+#             */
/*   Updated: 2023/05/11 13:48:55 by lsordo           ###   ########.fr       */
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
	printf("\n");
}

void	tmp_freelst(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	printf("=== debug tmp_freelst ===\n");
	while (lst)
	{
		printf("debug: content\n");
		if (lst->content)
			free(lst->content);
		printf("debug: list\n");
		if (lst)
			free(lst);
		printf("debug: control\n");
		tmp = lst->next;
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
	printf("=== debug tmp_freearr ===");
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	tmp_freedisplay(t_display *d)
{
	printf("=== debug freedisplay ===\n");
	// tmp_prtlst(d->pdata->file_data);
	// if (d && d->pdata && d->pdata->file_data)
	// 	tmp_freelst(d->pdata->file_data);
	if (d && d->pdata && d->pdata->textures_path)
		ft_freesplit_2(d->pdata->textures_path, 5);
	if (d && d->pdata && d->pdata->colors_path)
		ft_freesplit_2(d->pdata->colors_path, 3);
	if (d && d->pdata && d->pdata->map)
		ft_freesplit(d->pdata->map);
	if (d && d->pdata && d->pdata->map_testfill)
		ft_freesplit(d->pdata->map_testfill);
	if (d && d->pdata)
		free(d->pdata);
	if (d)
		free(d);
}
