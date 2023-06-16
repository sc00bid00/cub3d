/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_3_gettable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:46:39 by lsordo            #+#    #+#             */
/*   Updated: 2023/06/16 09:31:28 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
			return (false);
		i++;
	}
	return (true);
}
