/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 09:37:46 by kczichow          #+#    #+#             */
/*   Updated: 2023/06/16 09:40:09 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
