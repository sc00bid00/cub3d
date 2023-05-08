/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:49:02 by lsordo            #+#    #+#             */
/*   Updated: 2023/05/08 18:22:54 by lsordo           ###   ########.fr       */
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
		printf("%s", tmp->content);
		tmp = tmp->next;
	}
}

void	tmp_freelst(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	printf("=== debug tmp_freelst ===\n");
	while (lst)
	{
		free(lst->content);
		free(lst);
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
		printf("%s\n", arr[i]);
		i++;
	}
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
	if (d && d->pdata && d->pdata->fdata)
		tmp_freelst(d->pdata->fdata);
	if (d && d->pdata && d->pdata->tex)
		ft_freesplit_2(d->pdata->tex, 5);
	if (d && d->pdata && d->pdata->info)
		ft_freesplit_2(d->pdata->info, 3);
	if (d && d->pdata)
		free(d->pdata);
	if (d)
		free(d);
}
